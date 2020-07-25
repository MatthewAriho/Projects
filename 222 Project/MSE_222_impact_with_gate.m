function Ball_data = MSE_222_impact_with_gate(Ball_data)
    %calculating for impact situation using energy

    %calculating for a free fall

    %fixed variables to defined
    m=0.005*0.9; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t =0.0001; %predetermined value
    e=0.15; %coefficient of restitution
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
    
    New_data = zeros(1, 13);
    %calculations
    %Use energy analysis to determine ang velocity from the initial, under
    %no slip condition
    New_data(1) = ti+ delta_t; %time
    New_data(4) = Current_data(4)*e;
    New_data(2) = Current_data(2)*e; %vel in x
    New_data(3) = Current_data(3)*e;    %vel in y - check direction
    New_data(8) = xi+ (vxi)*(1-e)*delta_t; %pos in x - assuming change in velocity is so sudden it doesnt change until end of the interval
    New_data(9) = yi + vyi*(1-e)*delta_t; %pos in y


    %Used force analysis with no friction to find ang acc and then
    %tangential and normal acceleration
    New_data(5) = Current_data(5);       %acceleration in x
    New_data(6) = Current_data(6);        %acceleration in y - check sign
    New_data(7) = Current_data(7);
    New_data(10) = Current_data(10);   %magnitude of normal force acting on ball
    New_data(11) = Current_data(11); %centripetal forces
    New_data(12) = 0.005*-9.81;    %weight 
    New_data(13) = 0;    %force due to spring
    
    Ball_data = [Ball_data; New_data];
    
end