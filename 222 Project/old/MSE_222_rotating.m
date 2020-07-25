function Ball_data = MSE_222_rotating(Ball_data)
    %calculating for rotating component

    %fixed variables to defined
    m=0.005; %mass of the ball
    r=0.01; %radius of the ball
    g=9.81; %acceleration due to gravity

    
    %design parameters
    m_g=; %mass f gear
    r_g=; %radius of gear
    
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
    I = 0.4*m*r^2;
    I_g = 0.5*m_g*r^2 + (I+ m*(r_g+r)^2); %inertia of ball+gear combination from center of gear
    rotional_ti = 0.5 * (I) * wi^2;   % initial rotational KE
    transational_ti = 0.5 * m * vi^2;  % initial translational KE
  
    w_g = ((rotational_ti + translational_ti)/I_g)^0.5;     %assuming conservation of energy, the kinetic energy of the ball is transferred towards the rotational ke of the gear
    
    
    for i=delta_theta:delta_theta:pi/2
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
        index = i/delta_theta;
        t_delta_t= i/w_g; 
        New_data(index, 1) = t+ t_delta_t; %time
        New_data(index, 4) = w_g;
        New_data(index, 2) = -w_g*r*cos(i); %vel in x
        New_data(index, 3) = -w_g*r*sin(i);    %vel in y
        New_data(index, 8) = xi + i*cos(i); %pos in x
        New_data(index, 9) = yi - i*sin(i); %pos in y
       

        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
        New_data(index, 5) = m*(w_g^2)*r*sin(i);       %acceleration in x
        New_data(index, 6) = -m*(w_g^2)*r*cos(i);        %acceleration in y
        New_data(index, 7) = 0;
        New_data(index, 10) = m*g*cos(i);   %magnitude of normal force acting on ball
        New_data(index, 11) = m*(w_g^2)*r; %centripetal forces
        New_data(index, 12) = m*g;    %weight 
        New_data(index, 13) = 0;    %force due to spring
        
    end
    
    Ball_data = [Ball_data; New_data];
    
end