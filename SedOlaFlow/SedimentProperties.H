    Info<< "Reading sediment properties\n" << endl;

    // Define dictionary
    IOdictionary sedimentDict
    (
        IOobject
        (
            "sedimentDict",
            runTime.constant(),//located at constant folder
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );
        
    dimensionedScalar D50sed
    (
    sedimentDict.lookupOrDefault
    (
        "D50sed",
        dimensionedScalar("D50sed", dimensionSet(0, 1, 0, 0, 0, 0, 0), 0.0002)
    )
    );