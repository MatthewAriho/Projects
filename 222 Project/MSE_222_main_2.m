% MSE 222 Dynamics Project MATALB Simulation
% Authors- Matthew Ariho, Aryan Archan, Prabnoor Singh, Kedar Kattimani
% March-April 2020

% right top of board is 0,0, units are standard SI unless otherwise noted. 
clc
clear all;
m=0.005*0.9; %mass of the ball
r=0.01; %radius of the ball
g=9.81; %acceleration due to gravity
W= m*g;
e = 0.15; %coefficient of restitution
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
% cla;
% figure
% rows = size(Ball_data, 1);
% %%<<<<<<< HEAD
%  plot(Ball_data(1:rows, 8), Ball_data(1:rows, 9)); % grab a quick graph of position 
%  axis([-0.05 1 -1 0.1])
%  hold on
%  pause(5);
%  
% figure
% plot(Ball_data(1:rows, 1), Ball_data(1:rows, 2)); % grab a quick graph of position 
% xlabel(['Time']);
% ylabel(['X Velocity']);
% hold on
% 
% figure 
% plot(Ball_data(1:rows, 1), Ball_data(1:rows, 3)); % grab a quick graph of position 
% xlabel(['Time']);
% ylabel(['Y Velocity']);
% 
% figure 
% plot(Ball_data(1:rows, 1), Ball_data(1:rows, 5)); % grab a quick graph of position 
% xlabel(['Time']);
% ylabel(['X Acceleration']);
% 
% figure 
% plot(Ball_data(1:rows, 1), Ball_data(1:rows, 6)); % grab a quick graph of position 
% xlabel(['Time']);
% ylabel(['Y Accelereation']);
% 
%  %comet(Ball_data(:,2),Ball_data(:,3))
% % % 
% %  for n = 1:1:rows-1
% %     plot(Ball_data(n, 2), Ball_data(n, 3), 'or'); 
% %     pause(Ball_data(n, 1)/100);
% %  end
% %%=======
% 
% subplot(3,2,1:4)    % make a subplot and put the position in it
% plot(Ball_data(1:rows, 8), Ball_data(1:rows,9))
% grid on
% title('Position of Center of Mass');
% xlabel('Horizontal Position (m)');
% ylabel('Vertical Position (m)');
% hold on
% p1=plot(Ball_data(1:rows, 8), Ball_data(1:rows,9),'Marker','o','MarkerFaceColor','r');    % this is the ball that will be animated
% axis([-0.05 1 -1 0.05]) % getting the axes set up 
% 
% subplot(3, 2, 5)    % subplot for x velocity
% plot(Ball_data(1:rows, 1), Ball_data(1:rows,2))
% grid on
% title('X Velocity');
% xlabel('Time (s)');
% ylabel('Velocity (m/s)');
% axis([0 20 -2 3.5])
% hold on
% p2=plot(Ball_data(1:rows, 1), Ball_data(1:rows,2),'Marker','o','MarkerFaceColor','r');
% 
% subplot(3, 2, 6)    % subplot for y velocity
% plot(Ball_data(1:rows, 1), Ball_data(1:rows,3))
% grid on
% title('Y Velocity');
% xlabel('Time (s)');
% ylabel('Velocity (m/s)');
% axis([0 20 -4 9])
% hold on
% p3=plot(Ball_data(1:rows, 1), Ball_data(1:rows,3),'Marker','o','MarkerFaceColor','r');
% hold off
% 
% for n = 1:1:rows-1
%     p1.XData = Ball_data(n, 8);  % update the x and Y data of the p1, p2, p3 plots in the subplot
%     p1.YData = Ball_data(n, 9);
%      p2.XData = Ball_data(n, 1);
%     p2.YData = Ball_data(n, 2);
%      p3.XData = Ball_data(n, 1);
%     p3.YData = Ball_data(n, 3);
%     drawnow
%    pause((Ball_data(n+1, 1)-Ball_data(n, 1))*1.5);
% end
% 
