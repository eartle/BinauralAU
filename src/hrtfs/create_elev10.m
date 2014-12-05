% ELEV0
fid = fopen ('hrtf_elev10.h','w');
%elev0
for i = 0:5:180
    % get the correct file name
    filename = sprintf('elev10\\H10e%03da.wav', i);
        
    % read and resample the wav file
    wavin = wavread(filename); 
    impulseresponse_left = wavin(1:128,1);
    
    % output the samples in the correct format
    fprintf(fid,'%1.15f,\n',impulseresponse_left);
end

for i = 0:5:180
    % get the correct file name
    filename = sprintf('elev10\\H10e%03da.wav', i);
        
    % read and resample the wav file
    wavin = wavread(filename); 
    impulseresponse_right = wavin(1:128,2);
    
    % output the samples in the correct format
    fprintf(fid,'%1.15f,\n',impulseresponse_right);
end
fclose(fid);