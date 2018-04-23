%% Turn Ankle Module On or Off
% This script sets the indices of multiple selectors to select the right
% channels in order to let the model work for either with/without ankle

if AnkleModuleOn == 1
    SelectorCartPos = [1:12 19:27]; SelectorCartPosSize = 33; 
    SelectorLOPESIn = 1:10; SelectorLOPESInSize = 10;
    SelectActive = 1:10; SelectorLOPESModelPosSize = 13; 
    SelectorLOPESModelPosPelvisRot = 12:13;
        
    %% Scopes
    SelectorScopesLeft = 3:6; SelectorScopesSize = 10;
    SelectorScopesRight = 7:10;
    
elseif AnkleModuleOn == 0
    SelectorCartPos = [1:21]; SelectorCartPosSize = 21; 
    SelectorLOPESIn = [1:5 7:9]; SelectorLOPESInSize = 8;
    SelectActive = 1:8; SelectorLOPESModelPosSize = 11;
    SelectorLOPESModelPosPelvisRot = 10:11;
       
    %% Scopes
    SelectorScopesLeft = 3:5; SelectorScopesSize = 8;
    SelectorScopesRight = 6:8;
end
