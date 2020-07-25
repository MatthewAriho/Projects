function Ball_data = MSE_222_free_fall(Ball_data, h)
    %calculating for a free fall

    %fixed variables to defined
    m=0.005; %mass of the ball
    r=0.01; %radius of the ball
    g=9.81; %acceleration due to gravity
    
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
    time+to_fall = (2*g*h)^2;
    
    for i=delta_t:delta_t:time_to_fall;
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
        index = i/delta_t;
        New_data(index, 1) = t+ i; %time
        New_data(index, 4) = 0;
        New_data(index, 2) = 0; %vel in x
        New_data(index, 3) = vyi+g*i;    %vel in y - check direction
        New_data(index, 8) = xi+ vxi*i; %pos in x
        New_data(index, 9) = yi + vyi*i+ 0.5*g*i^2; %pos in y
       

        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
        New_data(index, 5) = 0;       %acceleration in x
        New_data(index, 6) = g;        %acceleration in y - check sign
        New_data(index, 7) = 0;
        New_data(index, 10) = 0;   %magnitude of normal force acting on ball
        New_data(index, 11) = 0; %centripetal forces
        New_data(index, 12) = m*g;    %weight 
        New_data(index, 13) = 0;    %force due to spring
        
    end
    
    Ball_data = [Ball_data; New_data];
    
end