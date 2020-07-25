
global node;     
global element;  
global material; 
global section;  


%%%%node information:No,DOF, coordinate of node_X,Y, constraint
%%%%information_X,Y,Angle(1 is constraint, 0 is free),force on node
%%%%Fx,_Fy,_Moment
node=...
[ 1   2   0.0    0.0   0  0   0    0    0      0
  2   2   60.18     6.2    0  1   0    0    0      0
  3   2  38.632    58.973   0  0   0    0    -200.17      0
  4   2   -15.87843       46.35597    0  0   0    0    -1601.36   0
  5   2   -43.3889       5.2045    0  1   0    0   0    0
  6   2   43.5467       46.936    0  0   0    0    0   0];

%element information: Element No., node1, node2, Element Type(1 is Truss,2
%is Beam), Material No., Cross-Section No.

element=...
[   1   1   2       1   1    1
    2   2   6       1   1    1
    3   3   4       1   1    1
    4   1   4       1   1    1
    5   4   5       1   1    1
    6   1   6       1   1    1
    7   1   5       1   1    1
    8   3   6       1   1    1];

%Material information:Material No, Modulus of elasticity
material=[ 1   0.72e11];

%Cross-Section No, Cross-sectional area, Moment of Inertia, the Maximum
%distance from Neutral axis
section=...
[   1   1 1 1  ];
save('modelours.mat','node','element','material','section');
