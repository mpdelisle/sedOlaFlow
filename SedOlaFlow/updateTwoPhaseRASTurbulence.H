//TKE attenuation due to particle inertia effects is neglected here
// stratification
ESD4 = -(scalar(1.0)/beta)*(rho1*2.65/rho-1.0)*g & fvc::grad(beta);

// the following term is implemented in epsilon equation.
ESD5 = -(scalar(1.0)/beta)*(rho1*2.65/rho-1.0)*g & fvc::grad(beta);

// if ESD5 > 0, then it should be implemented, else, no
ESD5 = max(ESD5, scalar(0.0)*ESD5);