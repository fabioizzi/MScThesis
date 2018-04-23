% this script is called by nms_3Dmodel.mdl
warning('off','all')                % Needed for speed (Simulink gives warnings)

% clear;
addpath('.\param');

walkTypeList = [5];
% 1: normal walk
% 2: robust walk
% 3: Optimized walking at 0.65 m/s
% 4: Inverse Optimized walking at 0.65 m/s, general settings, with dists
% 5: Inverse Optimized walking at 1.2 m/s, general settings, with dists

%% PreNaming
CtrlPar_FP_R_List = []; CtrlPar_St_R_List = []; CtrlPar_Sw_R_List = [];
CtrlPar_Tr_R_List = []; CtrlPar_theta0_List = []; CtrlPar_FP_List = [];
CtrlPar_LL_List = []; CtrlPar_St_List = []; CtrlPar_Sw_List = [];
CtrlPar_Tr_List = []; CtrlPar_VelocityFile_List = []; 
theta0_control_List = []; maxLoad_control_List= [];

for i_walkType = 1:length(walkTypeList)
    walkType = walkTypeList(i_walkType);
    switch walkType
        case 1
            load('paramIC_02cm');	% paramIC
            load('param_02cm');  	% param
            CtrlPar_VelocityFile_List = [CtrlPar_VelocityFile_List; 1.2];
        case 2
            load('paramIC_10cm');   % paramIC
            load('param_10cm');     % param
            CtrlPar_VelocityFile_List = [CtrlPar_VelocityFile_List; 1.2];
        case 3
            load('paramIC_02cm');   % paramIC
            load('param_V64');     % param
            CtrlPar_VelocityFile_List = [CtrlPar_VelocityFile_List; 1.2];
        case 4
            load('paramIC_02cm');             % paramIC
            load('param_V35_inv_nAnkle');     % param (Inverse Opt at 0.65 m/s)
            CtrlPar_VelocityFile_List = [CtrlPar_VelocityFile_List; 0.65];
        case 5
            load('paramIC_02cm');             % paramIC
            load('param_V26_inv_nAnkle');     % param (Inverse Opt at 1.2 m/s)
            CtrlPar_VelocityFile_List = [CtrlPar_VelocityFile_List; 1];
    end
    
    % Checking for doubles in velocity, which should be avoided
    if length(unique(CtrlPar_VelocityFile_List(:,1)))<size(CtrlPar_VelocityFile_List,1)
        error('Velocities are the same for two paramSets'); 
    end
    
    % If paramSize is 82, it means no M11 was optimized. However, a full
    % parameter set is needed for the program to run. 
    % M11 is deactivated by adding parametrs with high thresholds (10,-10)
    % and zeros for the activation gain parameters.
    if size(param,1) == 82
        param = [param(1:35);[10;0;0;0;-10;0;0;0];param(36:end)];
    end
    
    % Running the several Param Scripts 
    setAnkleDepInd;
    nms_MechInit;
    setInitPar;
    setCtrlPar;

    %% Filling CntrlParam Lists (Used for interpolation if multiple are selected)
    CtrlPar_FP_R_List = [CtrlPar_FP_R_List; CtrlPar_FP_R];    CtrlPar_St_R_List = [CtrlPar_St_R_List; CtrlPar_St_R];    CtrlPar_Sw_R_List = [CtrlPar_Sw_R_List; CtrlPar_Sw_R];
    CtrlPar_Tr_R_List = [CtrlPar_Tr_R_List; CtrlPar_Tr_R];    CtrlPar_theta0_List = [CtrlPar_theta0_List; CtrlPar_theta0];    CtrlPar_FP_List = [CtrlPar_FP_List; CtrlPar_FP];
    CtrlPar_LL_List = [CtrlPar_LL_List; CtrlPar_LL];    CtrlPar_St_List = [CtrlPar_St_List; CtrlPar_St];    CtrlPar_Sw_List = [CtrlPar_Sw_List; CtrlPar_Sw];
    CtrlPar_Tr_List = [CtrlPar_Tr_List; CtrlPar_Tr];
    
    %% Mean trunk angle and maxLoad during walking/optimization
    if exist('maxLoad','var') && exist('meanTheta','var') 
        theta0_control_List(i_walkType) = meanTheta;
        maxLoad_control_List(i_walkType) = maxLoad;
    else
        theta0_control_List(i_walkType) = 0.1;
        maxLoad_control_List(i_walkType) = 1.2;
        disp('No Theta0 and maxLoad present in paramFile, set to standard')
    end
end