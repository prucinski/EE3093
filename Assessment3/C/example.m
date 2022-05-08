fileID = fopen('pulse.txt');
A = fscanf(fileID, '%f %f', [2 inf]);
plot(A(1,:), A(2,:))