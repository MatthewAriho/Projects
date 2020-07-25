% MSE 222 Dynamics Project MATALB Simulation
% Authors- Matthew Ariho, Aryan Archan, Prabnoor Singh, Kedar Kattimani
% March-April 2020

% right top of board is 0,0, units are standard SI unless otherwise noted. 
clc
clear all;
m=0.005*1; %mass of the ball
r=0.01; %radius of the ball
g=9.81; %acceleration due to gravity
W= m*g;
e=0.15*1; %coefficient of restitution
correction = 1.5*e*0.2;
Ball_data = [0,0,0,0,0,0,0,r,0,W, 0,W, 0]; % initial conditions - everything is zero
% size(Ball_data)
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

[Ball_data] = MSE_222_spring(Ball_data)  % get initial velocity from spring launch
[Ball_data] = MSE_222_flat(Ball_data, 0.29/2)    % roll horizontally
[Ball_data] = MSE_222_impact_with_gate(Ball_data) %impact with gate
[Ball_data] = MSE_222_flat(Ball_data, 0.29/2 - correction)
[Ball_data] = MSE_222_framp(Ball_data, 0.3169/2, 0.209)   %  ramp
[Ball_data] = MSE_222_impact_with_gate(Ball_data) %impact with gate
[Ball_data] = MSE_222_framp(Ball_data, 0.3169/2+ 0.5*correction, 0.209)   %  ramp
[Ball_data] = MSE_222_impact_with_wall(Ball_data) %impact with wall
[Ball_data] = MSE_222_free_fall(Ball_data, 0.0366)   % fall vertically
[Ball_data] = MSE_222_back_curve(Ball_data, 1.5*pi, 5.89, 0.035)  % first curve, right and down
[Ball_data] = MSE_222_bramp(Ball_data, 0.22/2, pi+0.349)   %  ramp
[Ball_data] = MSE_222_impact_with_gate(Ball_data) %impact with gate
[Ball_data] = MSE_222_bramp(Ball_data, 0.22/2 - 0*correction, pi+0.349)   %  ramp
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
[Ball_data] = MSE_222_rotating(Ball_data)   %  rotating element
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
[Ball_data] = MSE_222_free_fall(Ball_data, 0.046)   % fall vertically
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
[Ball_data] = MSE_222_back_curve(Ball_data, 1.5*pi, 6.06, 0.045) % second curve, left and down - change height
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
[Ball_data] = MSE_222_bramp(Ball_data, 0.313/2, pi+0.277)   %  ramp
[Ball_data] = MSE_222_impact_with_gate(Ball_data) %impact with gate
[Ball_data] = MSE_222_bramp(Ball_data, 0.313/2 - 1.5*correction, pi+0.277)   %  ramp
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
[Ball_data] = MSE_222_impact_with_wall(Ball_data) %impact with wall
[Ball_data] = MSE_222_free_fall(Ball_data, 0.0504)   % fall vertically
[Ball_data] = MSE_222_front_curve(Ball_data, pi, 1.5*pi, 0.085) % third curve, left and down
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
[Ball_data] = MSE_222_framp(Ball_data, 0.5/2, 0.0993)   %  ramp
[Ball_data] = MSE_222_impact_with_gate(Ball_data) %impact with gate
[Ball_data] = MSE_222_framp(Ball_data, 0.5/2 + 0.1* correction, 0.0993)   %  ramp
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)
% [Ball_data] = MSE_222_flat(Ball_data, 0.1895/2)    % roll horizontally - MIGHT BE POINTLESS - YET TO FIND OUT
% [Ball_data] = MSE_222_impact_with_gate(Ball_data) %impact with gate
% [Ball_data] = MSE_222_flat(Ball_data, 0.1895 - correction/2)
% pos = size(Ball_data, 1)
% Current_data =Ball_data(pos,:)

Ball_data;
%%impact
% 
%Reference- Code from the animation was generated using a blueprint provided by https://github.com/richarthurs/222-Project
cla;
figure
rows = size(Ball_data, 1);
%%<<<<<<< HEAD
 plot(Ball_data(1:rows, 8), Ball_data(1:rows, 9)); % grab a quick graph of position 
 axis([-0.05 0.6 -0.7 0.1])
 hold on
 pause(5);
 
figure
plot(Ball_data(1:rows, 1), Ball_data(1:rows, 2)); % grab a quick graph of position 
xlabel(['Time']);
ylabel(['X Velocity']);
hold on

figure 
plot(Ball_data(1:rows, 1), Ball_data(1:rows, 3)); % grab a quick graph of position 
xlabel(['Time']);
ylabel(['Y Velocity']);

figure 
plot(Ball_data(1:rows, 1), Ball_data(1:rows, 5)); % grab a quick graph of position 
xlabel(['Time']);
ylabel(['X Acceleration']);

figure 
plot(Ball_data(1:rows, 1), Ball_data(1:rows, 6)); % grab a quick graph of position 
xlabel(['Time']);
ylabel(['Y Accelereation']);

subplot(3,2,1:4)    % make a subplot and put the position in it
plot(Ball_data(1:rows, 8), Ball_data(1:rows,9))
grid on
title('Position of Center of Mass');
xlabel('Horizontal Position (m)');
ylabel('Vertical Position (m)');
hold on
p1=plot(Ball_data(1:rows, 8), Ball_data(1:rows,9),'Marker','o','MarkerFaceColor','r');    % this is the ball that will be animated
axis([-0.05 0.6 -0.6 0.05]) % getting the axes set up 

subplot(3, 2, 5)    % subplot for x velocity
plot(Ball_data(1:rows, 1), Ball_data(1:rows,2))
grid on
title('X Velocity');
xlabel('Time (s)');
ylabel('Velocity (m/s)');
axis([0 20 -2 3.5])
hold on
p2=plot(Ball_data(1:rows, 1), Ball_data(1:rows,2),'Marker','o','MarkerFaceColor','r');

subplot(3, 2, 6)    % subplot for y velocity
plot(Ball_data(1:rows, 1), Ball_data(1:rows,3))
grid on
title('Y Velocity');
xlabel('Time (s)');
ylabel('Velocity (m/s)');
axis([0 20 -4 9])
hold on
p3=plot(Ball_data(1:rows, 1), Ball_data(1:rows,3),'Marker','o','MarkerFaceColor','r');
hold off

for n = 1:1:rows-1
    p1.XData = Ball_data(n, 8);  % update the x and Y data of the p1, p2, p3 plots in the subplot
    p1.YData = Ball_data(n, 9);
     p2.XData = Ball_data(n, 1);
    p2.YData = Ball_data(n, 2);
     p3.XData = Ball_data(n, 1);
    p3.YData = Ball_data(n, 3);
    drawnow
   pause((Ball_data(n+1, 1)-Ball_data(n, 1))*1.5);
end
% 
function Ball_data = MSE_222_flat(Ball_data, length)
    %calculating a flat path using energy, force eqns

    %fixed variables to defined
    m=0.005*1; %mass of the ball
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

function Ball_data = MSE_222_framp(Ball_data, length, angle)
    
    %calculating a straight ramp using energy

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t= 0.001; %predetermined in initial simulations
    
    %design parameters

    theta=angle;
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
    vxi=Current_data(2);%initial velocity of the center of gravity
    vyi=Current_data(3);%initial velocity of the center of gravity
    wi=Current_data(4); %initial angular velocity - might need to be adjusted
    
    New_data = zeros(1, 13);
    %calculations
    t= ti+delta_t; %initialising loop
    %%from the equations of motion, we used the moment of inertia at the
    %%bottom of the ball which leaves us with the following value of I
    I = 1.4*m*r^2;
    alpha = m*(-g)*r*sin(theta)/(I); %from equations of motion calculations
    delta_l= abs(wi)*r*delta_t + 0.5*abs(alpha)*r*delta_t;
    
    half = L/2;
    for i=delta_l:delta_l:L-1.5*delta_l
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
        t = t + delta_t;
        New_data(1) = t; %time
        w= sqrt((((I*wi^2)-2*m*g*i*sin(theta))/I)); %angular velocity
        New_data(4) = w;
        New_data(2) = w*r*cos(theta); %vel in x
        New_data(3) = -w*r*sin(theta);    %vel in y
        New_data(8) = xi + i*cos(theta); %pos in x
        New_data(9) = yi - i*sin(theta); %pos in y
       

        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
        New_data(5) = -alpha*r*cos(theta);       %acceleration in x
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

function Ball_data = MSE_222_rotating(Ball_data)
    %calculating for rotating component

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_theta= 0.05;
    
    %design parameters
    rho_g =0.2*1;
    m_g=(pi*(0.102*100)^2)*rho_g; %mass f gear
    r_g=0.102; %radius of gear
    e=0.15*1; % square of coefficent of restitution
    
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
    vi= (vxi^2 + vyi^2)^0.5;
    I = 0.4*m*r^2;
    I_g = 0.5*m_g*r^2 + (I+ m*(r_g+r)^2); %inertia of ball+gear combination from center of gear
    rotational_ti = 0.5 * (I) * wi^2;   % initial rotational KE
    translational_ti = 0.5 * m * vi^2;  % initial translational KE
    
    w_g = e*((rotational_ti + translational_ti)/I_g)^0.5;     %assuming conservation of energy, the kinetic energy of the ball is transferred towards the rotational ke of the gear
    
    
    for i=delta_theta:delta_theta:pi/2
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
       t_delta_t= i/w_g; 
       New_data(1) = ti+ t_delta_t; %time
       New_data(4) = w_g;
       New_data(2) = -w_g*r*cos(i); %vel in x
       New_data(3) = -w_g*r*sin(i);    %vel in y
       New_data(8) = xi + (r-r_g) * cos(pi/2 - i);; %pos in x 
       New_data(9) = yi +(r-r_g) - (r-r_g) * sin(pi/2 - i); %pos in y
%        x = xi + (r-R) * cos(pi/2 - i);  
%        y = yi -(r-R) + (r-R) * sin(pi/2 - i);

        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
       New_data(5) = m*(w_g^2)*r*sin(i);       %acceleration in x
       New_data(6) = -m*(w_g^2)*r*cos(i);        %acceleration in y
       New_data(7) = 0;
       New_data(10) = m*g*cos(i);   %magnitude of normal force acting on ball
       New_data(11) = m*(w_g^2)*r; %centripetal forces
       New_data(12) = m*g;    %weight 
       New_data(13) = 0;    %force due to spring
       Ball_data = [Ball_data; New_data];
    end
    
end

function Ball_data = MSE_222_bramp(Ball_data, length, angle)
    
    %calculating a straight ramp using energy

    %fixed variables to defined
    m=0.005*1; %mass of the ball
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

function Ball_data = MSE_222_free_fall(Ball_data, h)
    %calculating for a free fall

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t=0.005;
    
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
    time_to_fall_1 = (2*h/(-g))^0.5;
    
    for i=delta_t:delta_t:time_to_fall_1;
        %Use energy analysis to determine ang velocity from the initial, under
        %no slip condition
       New_data(1) = ti+ i; %time
       New_data(4) = 0;
       New_data(2) = 0; %vel in x
       New_data(3) = vyi+g*i;    %vel in y - check direction
       New_data(8) = xi+ vxi*i; %pos in x
       New_data(9) = yi + vyi*i+ 0.5*g*i^2; %pos in y
       

        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
       New_data(5) = 0;       %acceleration in x
       New_data(6) = g;        %acceleration in y - check sign
       New_data(7) = 0;
       New_data(10) = 0;   %magnitude of normal force acting on ball
       New_data(11) = 0; %centripetal forces
       New_data(12) = m*g;    %weight 
       New_data(13) = 0;    %force due to spring
       Ball_data = [Ball_data; New_data];
    end
  
    
end

function Ball_data = MSE_222_impact_with_wall(Ball_data)
    %calculating for impact situation using energy

    %calculating for a free fall

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t =0.005; %predetermined value
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
    New_data(4) = 0;
    New_data(2) = 0; %vel in x
    New_data(3) = 0;    %vel in y - check direction
    New_data(8) = xi; %pos in x
    New_data(9) = yi; %pos in y


    %Used force analysis with no friction to find ang acc and then
    %tangential and normal acceleration
    New_data(5) = 0;       %acceleration in x
    New_data(6) = g;        %acceleration in y - check sign
    New_data(7) = 0;
    New_data(10) = 0;   %magnitude of normal force acting on ball
    New_data(11) = 0; %centripetal forces
    New_data(12) = m*g;    %weight 
    New_data(13) = 0;    %force due to spring
    
    Ball_data = [Ball_data; New_data];
    
end

function [Ball_data] = MSE_222_spring(Ball_data)
    %calculating for loaded spring

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity

    %design parameters

    k=100*1; %spring constant
    delta_t= 0.01;  %time of contact
    x=0.01*1;  %length of spring that has been compressed
    delta = 0.0015*1; % In seconds
    s = 0.05*1; % uncompressed length

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
            New_data(i) = -m*g;
        end
        if(i==13)
            New_data(i) = (s/delta)*(5*k*m/7)^(1/2);
        end
    end
    New_data(1) = delta;
    % Assuming that the frictional force does not affect the acceleration of the ball, it moves at constant velocity.
    % i.e. The linear and angular acceleration remain zero.
    
    Ball_data = [Ball_data; New_data];

end

function Ball_data = MSE_222_front_curve(Ball_data, theta_1, theta_2, R )
    %calculating a curved ramp using energy

    %calculating a straight ramp using energy

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t= 0.005; %predetermined in initial simulations
    delta_theta=0.05;
    
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
    
    New_data = zeros(1, 13);
    %calculations
    t= ti+delta_t; %initialising loop
    %%from the equations of motion, we used the moment of inertia at the
    %%bottom of the ball which leaves us with the following value of I
    I_g= 0.4*m*r^2;
    I = 1.4*m*r^2;
    
    % Initial energies
    vi= (vxi^2 + vyi^2)^0.5;
    rotational_ti = 0.5 * (I_g) * wi^2;   % initial rotational KE
    translational_ti = 0.5 * m * vi^2;  % initial translational KE
    gravitational_vi = m * g * (R-r);  % gravitational potential Energy
    
    theta_start = theta_1 +delta_theta;
    
    for i= theta_start:delta_theta:theta_2
       %Use energy analysis to determine ang velocity from the initial, under
        %no slip conditio
        
       New_data(8) = xi + (R-r)*(1+cos(i)); %pos in x
       New_data(9) = yi + (R-r)*sin(i); %pos in y
        
       New_data(1) = ti+time_to_fall(m, r, R, wi, theta_1, i); %time
       
       w=-(((rotational_ti + translational_ti + m*g*(R-r)*(New_data(9)))/(0.5*I)))^0.5; %angular velocity
       New_data(4) = w;
       New_data(2) = w*r*sin(i); %vel in x
       New_data(3) = -w*r*cos(i);    %vel in y
        
        alpha = m*g*r*cos(i)/I;
        %Used force analysis with no friction to find ang acc and then
        %tangential and normal acceleration
       New_data(5) = sin(i)*(alpha*r)+(w^2)*r*cos(i);       %acceleration in x - check signs
       New_data(6) = -cos(i)*(alpha*r)+(w^2)*r*sin(i);        %acceleration in y
       New_data(7) = alpha;
       New_data(10) = -m*New_data(5)/sin(i);   %magnitude of normal force acting on ball
       New_data(11) = m*R*(w^2); %centripetal forces
       New_data(12) = m*g;    %weight 
       New_data(13) = 0;    %force due to spring
       Ball_data = [Ball_data; New_data];
        
    end   
    %t_time = time_to_fall(m, r, R, wi, theta1, theta2) ; %%increment theta my a constant value until to hit thetaend, through each iteration, find t and all the other variable values. increment theta such that we have 100 iterations between the start and end

end

function Ball_data = MSE_222_impact_with_gate(Ball_data)
    %calculating for impact situation using energy

    %calculating for a free fall

    %fixed variables to defined
    m=0.005*1; %mass of the ball
    r=0.01; %radius of the ball
    g=-9.81; %acceleration due to gravity
    delta_t =0.0001; %predetermined value
    e=0.15*1; %coefficient of restitution
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

function Ball_data = MSE_222_back_curve(Ball_data, theta_1, theta_2, R )
%calculating a curved ramp using energy

%calculating a straight ramp using energy

%fixed variables to defined
m=0.005*1; %mass of the ball
r=0.01; %radius of the ball
g=9.81; %acceleration due to gravity
delta_t= 0.005; %predetermined in initial simulations
delta_theta= 0.01;

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

New_data = zeros(1, 13);
%calculations
t= ti+delta_t; %initialising loop
%%from the equations of motion, we used the moment of inertia at the
%%bottom of the ball which leaves us with the following value of I
I_g= 0.4*m*r^2;
I = 1.4*m*r^2;

% Initial energies
vi= (vxi^2 + vyi^2)^0.5;
rotational_ti = 0.5 * (I_g) * wi^2;   % initial rotational KE
translational_ti = 0.5 * m * vi^2;  % initial translational KE
gravitational_vi = m * g * (R-r);  % gravitational potential Energy
theta_start= theta_1+delta_theta;
for i= theta_start:delta_theta:theta_2
    %index = (i-theta_1)/delta_theta;
    %Use energy analysis to determine ang velocity from the initial, under
    %no slip condition 
   New_data(8) = xi - (R-r)*(1-cos(1.5*pi - i)); %pos in x
   New_data(9) = yi + (R-r)*sin(1.5*pi - i); %pos in y

   New_data(1) = ti+ time_to_fall(m, r, R, wi, theta_1, i); %time

   w=(((rotational_ti + translational_ti + m*g*(r-R)*(New_data(9)))/(0.5*I)))^0.5; %angular velocity
   New_data(4) = w;
   New_data(2) = vxi-w*r*cos(i); %vel in x
   New_data(3) = w*r*sin(i);    %vel in y

    alpha = -m*g*r*cos(1.5*pi -i)/I;
    %Used force analysis with no friction to find ang acc and then
    %tangential and normal acceleration
   New_data(5) = cos(1.5*pi -i)*(-alpha*r)+(w^2)*r*sin(1.5*pi -i);       %acceleration in x - check signs
   New_data(6) = -sin(1.5*pi -i)*(alpha*r)-(w^2)*r*cos(1.5*pi -i);        %acceleration in y
   New_data(7) = alpha;
   New_data(10) = -m*New_data(5)/sin(1.5*pi -i);   %magnitude of normal force acting on ball
   New_data(11) = m*R*(w^2); %centripetal forces
   New_data(12) = m*g;    %weight 
   New_data(13) = 0;    %force due to spring
   Ball_data = [Ball_data; New_data];
end   
%t_time = time_to_fall(m, r, R, wi, theta1, theta2) ; %%increment theta my a constant value until to hit thetaend, through each iteration, find t and all the other variable values. increment theta such that we have 100 iterations between the start and end
end


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
