% ELEV0
fid = fopen ('hrtf_elev40.h','w');

array = [0 6 13 19 26 32 39 45 51 58 64 71 77 84 90 96 103 109 116 122 129 135 141 148 154 161 167 174 180];

for i = 1:29
    % get the correct file name
    filename = sprintf('elev40\\H40e%03da.wav', array(i));
        
    % read and resample the wav file
    wavin = wavread(filename); 
    impulseresponse_left = wavin(1:128,1);
    
    % output the samples in the correct format
    fprintf(fid,'%1.15f,\n',impulseresponse_left);
   
end

for i = 1:29
    % get the correct file name
    filename = sprintf('elev40\\H40e%03da.wav', array(i));
        
    % read and resample the wav file
    wavin = wavread(filename); 
    impulseresponse_right = wavin(1:128,2);
    
    % output the samples in the correct format
    fprintf(fid,'%1.15f,\n',impulseresponse_right);
end
fclose(fid);