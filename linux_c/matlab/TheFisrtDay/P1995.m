function P1995()
    year = 1900 : 10 : 2010;
    product = [75.995, 91.972, 105.711, 123.203, 131.699, 150.697, 179.323, 203.212, 226.505, 249.633, 256.344, 267.893];
    p1995 = interp1(year, product, 1995);
    disp(p1995);
    x = 1900 : 2010;
    y = interp1(year, product, x, 'cubic');
    plot(year, product, 'o', x, y);
end

