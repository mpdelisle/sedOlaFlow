volScalarField ESD4
(
    IOobject
    (
        "ESD4",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    -(scalar(1.0)/beta)*(rho1*2.65/rho-1.0)*g & fvc::grad(beta)
);

volScalarField ESD5
(
    IOobject
    (
        "ESD5",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    -(scalar(1.0)/beta)*(rho1*2.65/rho-1.0)*g & fvc::grad(beta)   
);
// if ESD5 > 0, then it should be implemented, else, no
ESD5 = max(ESD5, scalar(0.0)*ESD5);

// Construct incompressible turbulence model
autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, mixture)
);