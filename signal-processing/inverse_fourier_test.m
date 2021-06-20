function exit_code = inverse_fourier_test();
  % Dirac delta function
  dirac = @(t) 1.0 / (0.01 * sqrt(pi)) .* exp(-(t ./ 0.01).^2);
  
  % Let amp(s) be the fourier transform of the musical chord C
  % Note 1 = 261.63 Hz
  % Note 2 = 329.63 Hz
  % Note 3 = 392.00 Hz
  amp = @(s) dirac(s - 261.63) + dirac(s - 329.63) + dirac(s - 392.00);
  
  % Let signal(t) be the musical chord C
  signal = @(t) inverse_fourier(amp, 200, 400, 20000, t);
  
  %X = 200:0.01:400;
  %Y = amp(X);
  %plot(X, Y);
  
  X = 0:0.01:1;
  Y = signal(X);
  plot(X, Y);
  
  exit_code = 0;
endfunction;
