function Ball_data = MSE_222_back_curve(Ball_data, theta_1, theta_2, R )
    %calculating a curved ramp using energy

    %calculating a straight ramp using energy

    %fixed variables to defined
    m=0.005; %mass of the ball
    r=0.01; %radius of the ball
    g=9.81; %acceleration due to gravity
    delta_t= 0.01; %predetermined in initial simulations
    
    %design parameters
    %initial conditions
    %initial conditions for relevant parameters
    
    %Ball_data matrix col data and index
    %1-t
    %2- vel in x
    %3- vel in y
    %4- ang vel
    %5- accel in x
    %6- accel in y
    %7- ang acc
    %8- position in x (relative to top of board (0,0))
    %9- position in y (relative to top of board (0,0))
    %10- normal forces acting on ball
    %11- cetripetal forces on ball
    %12- weight
    %13- force due to spring
    %find position in matrix
    pos = size(Ball_data, 1);
    Current_data =Ball_data(pos,:);
    ti=Current_data(1);%time
    xi=Current_data(8); %position in x
    yi=Current_data(9); %position in y
    vxi=Current_data(2);%initial velocity of the center of gravity
    vyi=Current_data(3);%initial velocity of the center of gravity
    wi=Current_data(4); %initial angular velocity - might need to be adjusted
    
    New_data = (zeros, 13);
    %calculations
    t= ti+delta_t; %initialising loop
    %%from the equations of motion, we used the moment of inertia at the
    %%bottom of the ball which leaves us with the following value of I
    I_g= 0.4*m*r^2;
    I = 1.4*m*r^2;
    
    % Initial energies
    
    rotional_ti = 0.5 * (I_g) * wi^2;   % initial rotational KE
    transational_ti = 0.5 * m * vi^2;  % initial translational KE
    gravitational_vi = m * g * (R-r);  % gravitational potential Energy

    n=100;
    delta_theta= (theta_2-theta_1)/n;
    start = theta_start+delta_theta;
    
    New_data = (zeros, 13);
    
    for int i= theta_start:delta_theta:theta_end
        index = (i-theta_1)/delta_t;
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
        index = i/delta_l;
        
        New_data(index, 8) = xi + (R-r)*cos(1.5*pi - i); %pos in x
        New_data(index, 9) = yi - (R-r)*(1-sin(1.5*pi - i)); %pos in y
        
        New_data(index, 1) = time_to_fall(m, r, R, wi, theta1, i); %time
        
        w=(((rotational_ti + translational_ti + m*g*(r-R)*(New_data(index,9)))/(I)))^0.5; ; %angular velocity
        New_data(index, 4) = w;
        New_data(index, 2) = -w*r*sin(i); %vel in x
        New_data(index, 3) = -w*r*cos(i);    %vel in y
        
        alpha = -m*g*r*cos(i)/I;
        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
        New_data(index, 5) = cos(i)*(-alpha*r)+(w^2)*r*sin(i);       %acceleration in x - check signs
        New_data(index, 6) = -sin(i)*(alpha*r)-(w^2)*r*cos(i);;        %acceleration in y
        New_data(index, 7) = alpha;
        New_data(index, 10) = -m*ax/sin(i);   %magnitude of normal force acting on ball
        New_data(index, 11) = m*R*(w^2); %centripetal forces
        New_data(index, 12) = m*g;    %weight 
        New_data(index, 13) = 0;    %force due to spring
        Ball_data = [Ball_data; New_data]
    end   
    %t_time = time_to_fall(m, r, R, wi, theta1, theta2) ; %%increment theta my a constant value until to hit thetaend, through each iteration, find t and all the other variable values. increment theta such that we have 100 iterations between the start and end

    end