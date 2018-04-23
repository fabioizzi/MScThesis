function SaveSLRTData(filenameTemplate, SLRTFileName)
% function SaveSLRTData([filenameTemplate], [SLRTFileName])
%
% Saves the data from the file DATA.DAT, situated on the 'default SLRT
% target' (see slrtexplr) to a local file as a Matlab (.mat) file.
%
% If filenameTemplate is not given, it defaults to 'SLRT_%d_%t.mat'
%     (saving in the current directory)
% If SLRTFileName is not given, it defaults to 'DATA.dat'
%
% filenameTemplate is used as a template for the filename (can include a path).
% The following specifiers are recognized:
% %d -> 1602227  (Date, YYMMDD)
% %t -> 125323     (Time, HHMMSS)
% %i -> 01         (Trial number. It finds the largest trial number already
%                   existing, adds one and proposes that. Doesn't work well 
%                   together with %t, since usually there doesn't exist a
%                   trial number with that specific time)
% The date and time are the date/time at the moment of executing this
% function.
% 
% If a file is about to be overwritten, this function will ask whether this
% is really what you want (but it allows you to do it).

if ~exist('filenameTemplate','var')
    filenameTemplate = 'SLRT_%d_%t.dat';
end;

if ~exist('SLRTFileName','var')
    SLRTFileName = 'DATA.dat';
end;


disp('Asking whether to save the data...');
button = questdlg(['Do you want to download the ',SLRTFileName,' from the Simulink RealTime PC?'],'Save data?','Yes','No','Yes');

if ~strcmp(button,'Yes')
    disp(['Not downloading ' SLRTFileName '. If you still want to save, you can manually call the save function again:']);
    fprintf(1,'  SaveSLRTData(''%s'',''%s'')\n',filenameTemplate, SLRTFileName);
    return
end;

% If we're here, we need to save the data.

% Suggest a filename to save
FilterSpec = '*.mat'; DialogTitle = 'Choose a file name';
nw = now;
dateString = datestr(nw,'yymmdd');
timeString = datestr(nw,'HHMM');
suggestedFileName = strrep(strrep(filenameTemplate,'%d',dateString),'%t',timeString);

% Trial number: we need to check all possible trial numbers and see which
% is the highest existing one.
if ~isempty(strfind(suggestedFileName,'%i'))
    % Check for extension
    [~,~,ext] = fileparts(suggestedFileName);
    if isempty(ext)
        % Then there is no extension; add default
        suggestedFileName = [suggestedFileName '.mat'];
    end;
    for trialIndex = (99:-1:1); % No 0th experiment
        fileNameToCheck = strrep(suggestedFileName,'%i',sprintf('%02i',trialIndex));
        if exist(fileNameToCheck,'file')
            % Then we have to add one and use that number as the new index
            trialIndex = trialIndex+1; %#ok<FXSET>
            if trialIndex==100
                h=warndlg('Warning: More than 99 trials used! Please update the trial number yourself in the following save-as window.', ...
                    'Many trials','modal');
                uiwait(h);
            end;
            break;
        end;
    end;
    % When we're here, trialIndex is the right number to use
    suggestedFileName = strrep(suggestedFileName,'%i',sprintf('%02i',trialIndex));
end;

[FileName,PathName] = uiputfile(FilterSpec,DialogTitle,suggestedFileName);
if FileName == 0
    % Use pressed cancel
    disp('Not saving anything anyway. If you still want to save, you can manually call the following function:');
    fprintf(1,'  SaveSLRTData(''%s'',''%s'')\n',filenameTemplate, SLRTFileName);
    return;
end;

fullFileName = fullfile(PathName, FileName);

% File name is now known; let's do the work!

% Increase TCP/IP time-out (might be needed for retrieval of large packets)
% Requires the tg object. Skip if not available.
tg = slrt;
if exist('tg','var')
    if tg.get('CommunicationTimeOut') == 5 % Default
        try
            tg.set('CommunicationTimeOut',20);
        catch
            disp('Failed to increase TCP/IP timeout, attempt data retrieval anyway.');
        end
    end
else
    disp('No tg object available ');
end

% Retrieve data
s = ['Getting ' SLRTFileName ' from SLRT and saving to ' fullFileName '. This may take a while...'];
disp(s);
mbox = msgbox([s '(This window closes automatically when done)'],'Working...');
fs = tg.fs;
h=fs.fopen(SLRTFileName);
tmp = fs.fread(h);
fs.fclose(h);
SLRTdata = readxpcfile(tmp); %#ok<NASGU>
save( fullFileName ,'SLRTdata');

% Inform user that it has been done
close(mbox);
s = (['Saved data from ' SLRTFileName ' from SLRT as ' fullFileName '.']);
disp(s);
msgbox(s,'Done');
end