%% Settings Init File
%% This files loads the libraries for LOPES

% Settings of Model
AnkleModuleOn = 0;          %% With (1) or Without (0) Active Ankle. This settings is also used in setAnkleDepInd.m
modelName = 'LOPES_3D';     %% Model Name
xpcModelAvailable = 0;      %% If model previously has been build, this greatly increases build speed

%% Applying Settings
% Loading the right Library folders
% Turning AnkleModule on
if AnkleModuleOn == 1
    PATH.LOPES = what('..\..\Libraries_wAnkle\LopesDevelopmentLibrary');
    PATH.NMC = what('..\..\Libraries_wAnkle\NMC\');
else
    PATH.LOPES = what('..\..\Libraries_nAnkle\LopesDevelopmentLibrary\');
    PATH.NMC = what('..\..\Libraries_nAnkle\NMC\');
    load('AnkleData.mat');
end

%% Launch
addpath(genpath(PATH.LOPES.path));
addpath(genpath(PATH.NMC.path));
clear PATH

%% Load Simulink XPC model.
% If model has been build before, this loading of xpc model will
% make building again not needed
if xpcModelAvailable == 1
    xpc_file = xpc;
    xpc_file.load(modelName)
end

%% Open system
open_system(modelName);