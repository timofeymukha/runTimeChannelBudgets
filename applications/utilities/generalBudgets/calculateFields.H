        volSymmTensorField uipujpMean(uiujMean - symm(UMean * UMean));

        volScalarField uxpuxpMean(uipujpMean.component(symmTensor::XX));
        volScalarField uypuypMean(uipujpMean.component(symmTensor::YY));
        volScalarField uzpuzpMean(uipujpMean.component(symmTensor::ZZ));
        volScalarField uxpuypMean(uipujpMean.component(symmTensor::XY));

        volScalarField conv
        (
            IOobject
            (
                "conv",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -(uiCuiMean - (UMean & CuiMean))
        );

        volScalarField prod
        (
            IOobject
            (
                "prod",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -(uipujpMean && djuiMean)
        );

        volScalarField diff
        (
            IOobject
            (
                "diff",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            nu*(uiLuiMean - (UMean & LuiMean))
        );

        volScalarField diffSgs
        (
            IOobject
            (
                "diffSgs",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            uiLuiSgsMean - (UMean & LuiSgsMean)
        );

        volScalarField diss
        (
            IOobject
            (
                "diss",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -2*nu*(sijsijMean - (sijMean && sijMean))
        );

        volScalarField dissSgs
        (
            IOobject
            (
                "dissSgs",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -2*(nutsijsijMean - 2 * (sijMean && nutsijMean) +
            nutMean * (sijMean && sijMean))
        );

        volScalarField pDiff
        (
            IOobject
            (
                "pDiff",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            -(uiGcpMean - (UMean & GcpMean))
        );

        volScalarField vDiff
        (
            IOobject
            (
                "vDiff",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            diff - diss
        );

        volScalarField vDiffSgs
        (
            IOobject
            (
                "vDiffSgs",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            diffSgs - dissSgs
        );

        volScalarField trans
        (
            IOobject
            (
                "trans",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            conv - prod
        );


        conv.write();
        prod.write();
        diss.write();
        dissSgs.write();
        vDiff.write();
        vDiffSgs.write();
        pDiff.write();
        trans.write();
