% LopesDevelopmentLibraryOnPostLoadFcn.m
%
% Execute this script before compiling any Simulink model using the LopesDevelopmentLibrary.
% Use it to pre-set (configuration) variables.
d2r=@(d) d*(pi/180); % Convert degrees to radians

%% Sample time (be sure to use this in the model and not assume it will be
% the same always; we may change it to 1/1024 some day!)
LopesParams.ts = 0.001;
ts = LopesParams.ts; % Struct elements cannot be given as a parameter to embedded matlab functions, so it seems

%% Parameters for communication to LLC
% When we use a real xPC Target system, we can use the RealTime UDP blocks
% (using a separate network card for the UDP communication to the LLC).
% However, when we use a virtual machine, this is not possible, and we need
% to use the non-realtime UDP blocks (which communicate over the same
% network card as the Host-Target communication). We use variant submodels
% to switch between these; using the variable below we can choose which
% blocks are used when building (unfortunately, it is rather hard to put
% both in the system at the same time and switch during run-time. It is
% possible, but it involves changing the RT-UDP blocks that are provided by
% Matlab. I chose not to do that because it is a lot of work and it may
% become incompatible with new releases of Matlab.
%
% Additionally, the RealTime UDP blocks have evolved across Matlab
% versions. In an attempt to make the library work with different versions,
% Variant blocks are provided for multiple Matlab versions. An attempt is
% made to select the appropriate version automatically. If that fails, the
% user is asked to select a version manually.
%
% Actually, this variable should be called HLCParams.Communication.UseRealTimeUDP,
% but if we do that, then HLC_Gait will be recompiled each time we toggle
% the variable (because HLC_Gait depends on the global variable HLCParams,
% and is recompiled whenever it changes). Therefore, I made this a separate
% variable.
button = questdlg('Build for Realtime or for Non-Realtime? (your answer only affects the value of LopesUseRealTimeUDP)','RealTime?','RealTime','NonRealTime','RealTime');
if strcmp(button,'RealTime')
    LopesUseRealTimeUDP = 1; % Set to 1 or 0 before building to include either the realtime or non-realtime UDP blocks
else
    LopesUseRealTimeUDP = 0; % Set to 1 or 0 before building to include either the realtime or non-realtime UDP blocks
end;
clear button

% Obtain version identifier for determining which RealTime UDP block to
% use. Note, this is NOT identical to the actual version of Matlab, but it
% is identical to the set of blocks to be used (e.g., 2012b and 2013b use
% identical blocks, so they're both bound to the 2012b = 20122 version of
% the network blocks. 
v = ver('simulink');
switch v.Release
    % Below, only the known working options are listed. If another version
    % of Matlab is used, a warning is issued.
    case '(R2012b)', LopesUseRealTimeUDPVersion = 20122;
    case '(R2013b)', LopesUseRealTimeUDPVersion = 20122;
    case '(R2014b)', LopesUseRealTimeUDPVersion = 20142;
    case '(R2015b)', LopesUseRealTimeUDPVersion = 20152;
    otherwise, 
        disp(['Warning! It is unknown which version of RealTimeUDP blocks should ' ...
        'be used for this Matlab release ',v.Release,'. Please try (trial&error, set '... 
        'LopesUseRealTimeVersion to any of the above identifiers) and inform ' ...
        'Gijs van Oort about the outcome (and ask him for help if needed). ']);
        LopesUseRealTimeUDPVersion = -1;
end;

% Parameters for Non-realtime UDP (this can also be used when you simulate the system directly in Simulink).
%LopesParams.Communication.ipLLC_NonRT = char(['127.0.0.1',0,0,0,0,0,0]); % LocalHost (when simulating in Simulink)
LopesParams.Communication.ipLLC_NonRT = char(['192.168.56.1',0,0,0]); % VMWare. Added trailing zeros to create enough space to change into longer IP address just before running
%LopesParams.Communication.ipLLC_NonRT = char(['10.30.203.225',0,0]); % When connecting to the real LLC from Simulink

% Parameters for Realtime UDP:
LopesParams.Communication.ipSelf_RT = '10.30.203.226'; % ip of RT-UDP network card (no equivalent for non-rt; it then uses the target ip address)
% LopesParams.Communication.ipLLC_RT  = '10.30.203.101'; % Python Emulator on my own PC. No need for extra space here, address is stored in a different way.
LopesParams.Communication.ipLLC_RT  = '10.30.203.225'; % ip of the LLC. If emulating the LLC with my own laptop, I need to set the laptop's ip to this.
LopesParams.Communication.busSelf_RT = 2;
LopesParams.Communication.slotSelf_RT = 4;


% Parameters for both realtime and non-realtime UDP:
LopesParams.Communication.channel1SendPort = 25000;
LopesParams.Communication.channel1ReceivePort = 25001;
LopesParams.Communication.channel2SendPort = 25002;
LopesParams.Communication.channel2ReceivePort = 25003;
LopesParams.Communication.channel3SendPort = 25004;
LopesParams.Communication.channel3ReceivePort = 25005;
LopesParams.Communication.channel4SendPort = 25006;
LopesParams.Communication.channel4ReceivePort = 25007;
LopesParams.Communication.errorChannelReceivePort = 30001;

%% Variants for switching between RealTime UDP blocks and NonRealTime UDP blocks
% These are also responsible for switching UDP block versions across
% different Matlab versions
LopesVariant_Non_RT = Simulink.Variant('LopesUseRealTimeUDP==0');
LopesVariant_RT_2012b = Simulink.Variant('LopesUseRealTimeUDP~=0&&LopesUseRealTimeUDPVersion==20122');
LopesVariant_RT_2014b = Simulink.Variant('LopesUseRealTimeUDP~=0&&LopesUseRealTimeUDPVersion==20142');
LopesVariant_RT_2015b = Simulink.Variant('LopesUseRealTimeUDP~=0&&LopesUseRealTimeUDPVersion==20152');

%% Gait data
temp = load('LopesDevelopmentLibrary_GaitData.mat','GaitData');
LopesParams.GaitData = temp.GaitData;
clear temp;

%% Loading GaitParams Extra 
load('LopesDevelopmentLibrary_GaitDataExtra')
LopesParams.GaitDataStartLeft = GaitDataStartLeft;
LopesParams.GaitDataStopRight = GaitDataStopRight;
LopesParams.GaitDataStartRight = GaitDataStartRight;
LopesParams.GaitDataStopLeft = GaitDataStopLeft;

%% Stiffness parameters
% See the GaitGeneration|ConvertStiffness block.
LopesParams.Stiffness.Gamma = 2;
LopesParams.Stiffness.MaxJointStiffness =  [5000 20000 1500 1500 1500 1500 1500 1500];

%% Show message
disp('Executed LopesDevelopmentLibrary_LoadParameters.')
