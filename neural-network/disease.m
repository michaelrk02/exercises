function exit_code = disease();
    symptoms = [
        0; % Cough
        0; % Fatigue
        0; % Fever
        0; % Headache
        0; % Loss of smell
        0; % Shortness of breath
    ];
    weights = [
        0.00 2.00 2.00 4.00 0.00 0.00; % Flu
        2.00 2.00 2.00 0.00 4.00 4.00; % Coronavirus Disease
    ];

    activation = @(x) 1.0 ./ (1 .+ exp(-x));
    input_layer = [symptoms; 1.00];
    network = [weights [-5.00; -5.00]];
    output_layer = activation(network * input_layer);

    result = output_layer;
    disp(result);

    exit_code = 0;
end;
