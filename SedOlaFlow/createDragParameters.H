volScalarField DragK 
(
    "DragK",        
    (mixture.mu())/sqr(D50sed)
);

IOdictionary DragProperties
(
    IOobject
    (
        "DragProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

Switch GidaspowErgunWenyu
(
    DragProperties.lookup("GidaspowErgunWenyu")
);

Switch GidaspowSchillerNaumann
(
    DragProperties.lookup("GidaspowSchillerNaumann")
);

Switch Gibilaro
(
    DragProperties.lookup("Gibilaro")
);

///////////////////////////////////////////////////////////////////////
dictionary GidaspowErgunWenyuDict
(
    DragProperties.subDictPtr("GidaspowErgunWenyuCoeffs")
);

    dimensionedScalar alphaG
    (
        dimensionedScalar::lookupOrAddToDict
        (
            "alphaG",
            GidaspowErgunWenyuDict,
            150.0
        )
    );
    dimensionedScalar betaG
    (
        dimensionedScalar::lookupOrAddToDict
        (
            "betaG",
            GidaspowErgunWenyuDict,
            1.75
        )
    );

///////////////////////////////////////////////////////////////////////
dictionary GeneralDict
(
    DragProperties.subDictPtr("GeneralCoeffs")
);

dimensionedScalar gammaCoeff
(
    dimensionedScalar::lookupOrAddToDict
    (
        "gammaCoeff",
        GeneralDict,
        0.34
    )
);   
