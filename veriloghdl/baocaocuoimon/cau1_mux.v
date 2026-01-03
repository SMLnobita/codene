module cau1_mux(A, S, Y);
    input [7:0] A;
    input [2:0] S;
    output Y;
    
    wire [2:0] S_real;
    wire [2:0] S_not;
    wire [7:0] and_out;

    not U_IN0  (S_real[0], S[0]);
    not U_IN1  (S_real[1], S[1]);
    not U_IN2  (S_real[2], S[2]);

    not U_NOT0 (S_not[0],  S_real[0]);
    not U_NOT1 (S_not[1],  S_real[1]);
    not U_NOT2 (S_not[2],  S_real[2]);

    and U_AND7 (and_out[7], A[7], S_real[2], S_real[1], S_real[0]);
    and U_AND6 (and_out[6], A[6], S_real[2], S_real[1], S_not[0]);
    and U_AND5 (and_out[5], A[5], S_real[2], S_not[1],  S_real[0]);
    and U_AND4 (and_out[4], A[4], S_real[2], S_not[1],  S_not[0]);
    and U_AND3 (and_out[3], A[3], S_not[2],  S_real[1], S_real[0]);
    and U_AND2 (and_out[2], A[2], S_not[2],  S_real[1], S_not[0]);
    and U_AND1 (and_out[1], A[1], S_not[2],  S_not[1],  S_real[0]);
    and U_AND0 (and_out[0], A[0], S_not[2],  S_not[1],  S_not[0]);
    or  U_OR0  (Y, and_out[7], and_out[6], and_out[5], and_out[4], and_out[3], and_out[2], and_out[1], and_out[0]);
endmodule