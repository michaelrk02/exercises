% Inverse fourier transformation of 'func'
function result = inverse_fourier(func, smin, smax, frequencies, t);
  result = 0.0;
  ds = (smax - smin) / frequencies;
  for i = 1:frequencies;
    s = smin + i * ds;
    result = result + func(s) * cos(2 * pi * s * t) * ds;
  endfor;
endfunction;
