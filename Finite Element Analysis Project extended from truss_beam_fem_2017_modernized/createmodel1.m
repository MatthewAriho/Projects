
global node;     
global element;  
global material; 
global section;  


%%%%node information:No,DOF, coordinate of node_X,Y, constraint
%%%%information_X,Y,Angle(1 is constraint, 0 is free),force on node Fx,_Fy,_Moment
node=...
[ 1   2  0.0  1.0  0  0   0    0       0       0
  2   3  1.0  2.0  0  0   0    -1000  -1000    100
  3   3  1.0  0.0  1  1   1    0       0       0
  4   3  2.0  1.0  0  0   0    0       0       0];

%element information:No,node1,node2,Element Type(1 is Truss,2 is Beam),
%Material No, Cross-Section No

element=...
[   1   1   2       1   1    1
    2   1   3       1   1    1
    3   2   3       2   1    2
    4   3   4       2   1    2
    5   2   4       2   1    2];
 
%Material information:Material No, Modulus of elasticity
material=[ 1   2e11];
 
%Cross-Section No, Cross-sectional area, Moment of Inertia, the Maximum distance from Neutral axis
section=...
[   1   0.01  0.01   0.01
    2   0.02  2.0e-7  0.02];
save('model1.mat','node','element','material','section');
