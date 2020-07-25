% bike with mixed truss and beam

global node;     
global element;  
global material; 
global section;  


% node information: Node No., Degree of Freedom (DOF), X coordinate, Y
% coordinate, constraint along x,  constraint along y, constraint on 
% rotation(1 means constrained; 0 is free), load on the node Fx, Fy, and Moment

node=...
[ 1   2   0.0    0.0   0  0   0    0    0      0
  2   2   6.20     0.6    0  1   0    0    0      0
  3   2  4.6297    6.54597   0  0   0    0    -200.17      50.84
  4   2   -0.807       4.8331    0  0   0    0    -1601.36   406.745
  5   2   -4.2579       0.6    1  1   0    0    0   0];

%element information: Element No., node1, node2, Element Type(1 is Truss,2
%is Beam), Material No., Cross-Section No.

element=...
[   1   1   5       2   1    1
    2   2   3       2   1    1
    3   1   4       2   1    1
    4   4   5       2   1    2
    5   1   3       2   1    3];

%Material information:Material No, Modulus of elasticity
material=[ 1   2.28e11];

%Cross-Section No, Cross-sectional area, Moment of Inertia, the Maximum
%distance from Neutral axis
section=...
[   1   3.563697e-5 3.538353e-8 31.6e-3 
    2   2.873803e-5 1.855546-8 25.5e-3
    3   4.2988297e-5 6.2180812e-8 38.1e-3];
save('modelbikeours_3.mat','node','element','material','section');
