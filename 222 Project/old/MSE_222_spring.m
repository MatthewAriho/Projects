function [Ball_data] = MSE_222_spring(Ball_data)
    %calculating for loaded spring

    %fixed variables to defined
    m=0.005; %mass of the ball
    r=0.01; %radius of the ball
    g=9.81; %acceleration due to gravity

    %design parameters

    k=100; %spring constant
    delta_t= 0.01;  %time of contact
    x=0.01;  %length of spring that has been compressed
    delta = 0.001; % In seconds
    s = 0.05; % uncompressed length

    %initial conditions
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
    
    New_data = zeros(1, 13);
    %calculations

    v= ((5/7*k/m)^0.5)*x;
  
    for i=1:1:13
        if(i~=2||i~=4||i~=10||i~=13)
            New_data(i) = Current_data(i);
        end
        if(i==2)
            New_data(i) = v;
        end
        if(i==4)
            New_data(i) = v/r;
        end
        if(i==10)
            New_data(i) = m*g;
        end
        if(i==13)
            New_data(i) = (s/delta)*(5*k*m/7)^(1/2);
        end
    end
    New_data(1) = delta;
    % Assuming that the frictional force does not affect the acceleration of the ball, it moves at constant velocity.
    % i.e. The linear and angular acceleration remain zero.
    
    Ball_data = [Ball_data; New_data]

end
