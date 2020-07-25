function t = time_to_fall(m, r, R, w, low_lim, up_lim) 

    syms x;
    g=9.81;
    I = 1.4*m*r^2;
    %NUMERICAL INTEGRATION OF TIME_RANGE
    % breaking the big nasty scalar bits up to make it easier to read
    a = I;  
    b = a*w^2+2*m*g* (R-r);
    integral_fun = @(x) (a/b*(1- cos(x))).^0.5;    % note the element-wise exponent (instead of sqrt)
    t = integral(integral_fun, low_lim, up_lim); 
    t = real(t);  % get the time it takes to complete the curve and keep it real
    %%disp(time_to_fall)
    
end