function Ball_data = MSE_222_flat(Ball_data, length)
    %calculating a flat path using energy, force eqns

    %fixed variables to defined
    m=0.005*0.9; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t= 0.005; %predetermined in initial simulations
    
    %design parameters

    L=length;

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
    wi=Current_data(4); %initial angular velocity
   
    travel_time= L/vxi; %%Calculates time for travel
    %rows = ceil(travel_time/del_t);
    %New_data = zeros(rows,13)
    New_data = zeros(1,13);
    %calculations
    e_time = ti+ travel_time;
    t = ti+delta_t;
    for i=t:delta_t:e_time-2*delta_t
       %index = ceil((i-ti)/delta_t);
       New_data(1) = i;     % time
       New_data(8) = (vxi * i) + xi;    %pos in x
       for j=2:1:13
           if(j~=8)
               New_data(j) = Current_data(j);
           end
       end
        New_data(3) = 0;
       Ball_data = [Ball_data; New_data];
    end
end