function s = num2strjoin(terms, delimiter)
%num2str
% Given a 1D array of numbers and a delimiter, it returns the python
% equivalent of delimiter.join([str(x) for x in terms])
% 
% No error checking is done!
if nargin < 2
    delimiter = ' ';
end

%% main

n = numel(terms);
if n == 0
    s = '';
elseif n == 1
    s = num2str(terms(1));
else
    s='';
    for i=1:n-1
        s=[s,num2str(terms(i)),delimiter];
    end
    s=[s,num2str(terms(end))];
end
