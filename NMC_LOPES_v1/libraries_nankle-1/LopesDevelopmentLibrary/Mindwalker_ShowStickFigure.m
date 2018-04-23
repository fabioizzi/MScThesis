function ShowStickFigure(theta)
% Draws a stick figure based on the angles theta. If the figure already
% exists, it reuses it.
%
% Theta should be: [px, pz, lha, lhf, lkf, rha, rhf, rkf, torso]
%
%% Parameters
torsoLength=0.7;
upperLegLength = 0.5;
lowerLegLength= 0.5;
pelvisWidth = 0.4;


%% Check if figure exists; if not, build it
P1 = findobj('tag','StickFigurePlotLeft');
P2 = findobj('tag','StickFigurePlotRight');
if (isempty(P1))
    F=figure; clf;
    set(F,'name','Lopes StickFigure');
    P = plot3(0,0,0,'b-o',0,0,0,'r-o');
    P1 = P(1); P2 = P(2);
    set (P1,'tag','StickFigurePlotLeft');
    set (P2,'tag','StickFigurePlotRight');
   
    % Draw the origin frame
    frameSize = 0.4;
    L = line([0,0,0;frameSize,0,0],[0,0,0;0,frameSize,0], [0,0,0;0,0,frameSize]);
    set (L(1),'color',[1,0,0]); set (L(2),'color',[0,1,0]); set(L(3),'color',[0,0,1]);
    set(gca,'ydir','reverse')
    axis equal;xlim([-1,1]); ylim([-1,1]); zlim([0,2]); 
    xlabel('x'); ylabel('z');
    
	% Add a 2D and 3D button to the menu
    f=uimenu('label','2D/3D');
    uimenu(f,'Label','2D','callback','view([0,-1,0])');
    uimenu(f,'Label','3D','callback','view([-37.5,30])');

end;

%%
if (~exist('theta','var')),
    theta=zeros(1,9);
end;
%%
px=theta(1);
pz=theta(2);
lha=theta(3);
lhf=theta(4);
lkf=theta(5);
rha=theta(6);
rhf=theta(7);
rkf=theta(8);
torso = theta(9);

%% Calculate cartesian positions
pPelvis = [px; 1.0; pz];
pNeck = pPelvis + rotz(-torso)*[0;torsoLength;0];
pLeftHip = pPelvis-[0;0;pelvisWidth/2];
pRightHip = pPelvis+[0;0;pelvisWidth/2];
pLeftKnee = pLeftHip + rotx(lha) * rotz(lhf) * [0;-upperLegLength;0];
pLeftAnkle = pLeftKnee + rotx(lha) * rotz(lhf-lkf) * [0;-lowerLegLength;0];
pRightKnee = pRightHip + rotx(-rha) * rotz(rhf) * [0;-upperLegLength;0];
pRightAnkle = pRightKnee + rotx(-rha) * rotz(rhf-rkf) * [0;-lowerLegLength;0];

allLeft = [pLeftAnkle'; pLeftKnee'; pLeftHip'; pPelvis'; pNeck'];
allRight = [pPelvis'; pRightHip'; pRightKnee'; pRightAnkle'];
set(P1, 'xdata',allLeft(:,1), 'ydata',allLeft(:,3), 'zdata',allLeft(:,2));
set(P2, 'xdata',allRight(:,1), 'ydata',allRight(:,3), 'zdata',allRight(:,2));

function R=rotz(phi)
    % Returns rotation matrix with clockwise rotation around z axis
    s=sin(phi); c=cos(phi);
    R = [ c, -s, 0; s, c,0; 0,0,1];
    
function R=rotx(phi)
    % Returns rotation matrix with clockwise rotation around x axis
    s=sin(phi); c=cos(phi);
    R = [1,0,0; 0, c, -s; 0,s,c];