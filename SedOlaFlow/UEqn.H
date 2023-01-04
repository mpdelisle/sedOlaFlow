    MRF.correctBoundaryVelocity(U);

    surfaceScalarField muEff
    (
        "muEff",
        mixture.muf() + fvc::interpolate(rho*turbulence->nut())
    );

    volScalarField muEffv
    (
        "muEffv",
        mixture.mu() + rho*turbulence->nut()
    );
    

    /////////////////////////////////////////////////////////////////////////
    // calculate drag between phases
    /////////////////////////////////////////////////////////////////////////
    // common variables
    volScalarField Re = max(beta*mag(U)*rho*D50sed/mixture.mu(),scalar(1.0e-9));//Re cannot be zero

    volScalarField Cds // drag coefficients
    (
        neg(Re - 1000)*(24.0*(1.0 + 0.15*pow(Re, 0.687))/Re)
      + pos(Re - 1000)*0.44
    );
    
    if (GidaspowErgunWenyu)
    {
        volScalarField bp = pow(beta, -2.65);    

        Info<< "coeffs in GidaspowErgunWenyu a = " << alphaG.value() 
        <<", b = " << betaG.value() << endl;

        DragK == 
        pos(beta - 0.8)
          *(0.75*Cds*rho*mag(U)*bp/(beta*D50sed))
       +neg(beta - 0.8)
          *(alphaG*(scalar(1.0)-beta)*mixture.mu()/sqr(beta*D50sed)
                + betaG*rho*mag(U)/D50sed/sqr(beta));    
    }
    else if (GidaspowSchillerNaumann)
    {
        volScalarField bp = pow(beta, -2.65);
       
        DragK == 0.75*Cds*rho*mag(U)*bp/(beta*D50sed);
    }
    else if (Gibilaro)
    {
        volScalarField bp = pow(beta, -2.8);
    
        DragK == (17.3/Re + scalar(0.336))*rho*mag(U)*bp/(beta*D50sed);
    }
    Info<< "max(DragK) = " << max(DragK).value() << endl;
    
    /////////////////////////////////////////////////////////////////////////        
    // turbulent suspension   
    /////////////////////////////////////////////////////////////////////////        
    volVectorField susb
    (
        "susb",
        DragK*(rho*(turbulence->nut())+mixture.mu())/rho*fvc::grad(beta)
    );
    
    /////////////////////////////////////////////////////////////////////////        
    //added mass
    /////////////////////////////////////////////////////////////////////////
    volScalarField Cvm
    (
        "Cvm",        
        (scalar(1.0)-beta)/(beta)*gammaCoeff
    );
    Info<< "max(Cvm) = " << max(Cvm).value() << endl;
    
    ///////////////////////////////////////////////////////////////////////////
    // momentum eqs
    ///////////////////////////////////////////////////////////////////////////
    
    word schemeA("div(rhoPhi,U)");
    
    surfaceScalarField phiR = (scalar(1.0)/betaF)*muEff*mesh.magSf()*fvc::snGrad( beta );  
    
    volTensorField Rc = muEffv*dev2(T(fvc::grad( U*beta )));
    
    volVectorField Urb = fvc::grad( beta)/fvc::average( beta );
        
    fvVectorMatrix UEqn
    (
        // ACCELERATION      
        (scalar(1.0) + Cvm)/beta*
        (          
        fvm::ddt(rho, U) + MRF.DDt(rho, U)
        )
        // ADVECTION
        + (scalar(1.0)/beta)*fvm::div(rhoPhi/betaF, U, schemeA)
        
        // DIFFUSION
        // part 3.1
        - fvm::laplacian(muEff/betaF , U)
        + (scalar(1.0)/beta)*fvm::Sp(fvc::div(phiR),U)
        
        // part 3.2
        - fvc::div(Rc)
        - (Urb & Rc) // & -> inner product
                
        // DRAGs
        + fvm::Sp( ((scalar(1.0)-beta)/beta) * DragK, U)   // Ua is set to 0
        + susb
     ==
        fvOptions(rho, U)
    );

    UEqn.relax();

    fvOptions.constrain(UEqn);

