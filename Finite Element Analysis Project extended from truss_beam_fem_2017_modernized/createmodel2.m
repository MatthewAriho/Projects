
global node;     
global element;  
global material; 
global section;  


%%%%node information:No,DOF, coordinate of node_X,Y, constraint
%%%%information_X,Y,Angle(1 is constraint, 0 is free),force on node
%%%%Fx,_Fy,_Moment
node=...
[ 1   3  0.0    108.0  1  1   1    0  -4000  -80000
  2   3  120.0  108.0  0  0   0    0  -4000   80000
  3   2  120.0  0.0    1  1   1    0    0       0];

%element information:No,node1,node2,Element Type(1 is Truss,2 is Beam),
%Material No, Cross-Section No
element=...
[   1   1   2       2   1    1
    2   2   3       2   1    1];

%Material information:Material No, Modulus of elasticity
material=[ 1   30e6];

%Cross-Section No, Cross-sectional area, Moment of Inertia, the Maximum
%distance from Neutral axis
section=...
[   1   7.65  204.0  12.22];
save('model2.mat','node','element','material','section');
