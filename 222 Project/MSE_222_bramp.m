function Ball_data = MSE_222_bramp(Ball_data, length, angle)
    
    %calculating a straight ramp using energy

    %fixed variables to defined
    m=0.005*0.9; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t= 0.005; %predetermined in initial simulations
    
    %design parameters

    theta=pi-angle;
    L=length;

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
    vxi=Current_data(2);%initial velocity of the center of gravity - negative
    vyi=Current_data(3);%initial velocity of the center of gravity - negative
    wi=Current_data(4); %initial angular velocity - might need to be adjusted
    
    New_data = zeros(1, 13);
    %calculations
    t= ti+delta_t; %initialising loop
    %%from the equations of motion, we used the moment of inertia at the
    %%bottom of the ball which leaves us with the following value of I
    I = 1.4*m*r^2;
    alpha = m*(-g)*r*sin(theta)/(I); %from equations of motion calculations
    delta_l= abs(wi)*r*delta_t + 0.5*abs(alpha)*r*delta_t;
    
    
    for i=delta_l:delta_l:L
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
        t = t + delta_t;
        New_data(1) = t %time
        w= sqrt(((I*wi^2)+2*m*g*i*sin(theta))/I); %angular velocity
        New_data(4) = w;
        New_data(2) = -w*r*cos(theta); %vel in x
        New_data(3) = w*r*sin(theta);    %vel in y
        New_data(8) = xi - i*cos(theta); %pos in x
        New_data(9) = yi + i*sin(theta); %pos in y
       

        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
        New_data(5) = alpha*r*cos(theta);       %acceleration in x
        New_data(6) = -alpha*r*sin(theta);        %acceleration in y
        New_data(7) = alpha;
        New_data(10) = -m*New_data(5)/sin(theta);   %magnitude of normal force acting on ball
        New_data(11) = 0; %centripetal forces
        New_data(12) = m*g;    %weight 
        New_data(13) = 0;    %force due to spring
        delta_l= abs(w)*r*delta_t + 0.5*abs(alpha)*r*delta_t;
        Ball_data = [Ball_data; New_data];
    end
    
end