function exit_code = fourier_test();
  % Let signal(t) be the musical chord C
  % Note 1 = 261.63 Hz
  % Note 2 = 329.63 Hz
  % Note 3 = 392.00 Hz
  signal = @(t) cos(2 * pi * 261.63 .* t) .+ cos(2 * pi * 329.63 .* t) .+ cos(2 * pi * 392.00 .* t);
  
  % Let amp(s) be the fourier transform of signal(t)
  amp = @(s) fourier(signal, 0, 1, 1000, s);
  
  %X = 0:0.01:1;
  %Y = signal(X);
  %plot(X, Y);
  
  X = 200:0.01:400;
  Y = amp(X);
  plot(X, Y);
  
  exit_code = 0;
endfunction;
