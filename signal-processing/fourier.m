% Fourier transformation of 'func'
function result = fourier(func, tmin, tmax, samples, s);
  result = 0.0;
  dt = (tmax - tmin) / samples;
  for i = 1:samples;
    t = tmin + i * dt;
    result = result + func(t) * cos(2 * pi * t .* s) * dt;
  endfor;
  result = result / (tmax - tmin);
endfunction;
