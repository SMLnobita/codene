module HA(A, B, Sum, Carry);
    input A, B;
    output Sum, Carry;
    assign Sum   = A ^ B;
    assign Carry = A & B;
endmodule

module FA(A, B, Cin, Sum, Cout);
    input A, B, Cin;
    output Sum, Cout;
    assign Sum  = Cin ^ (A ^ B);
    assign Cout = (A & B) | (Cin & (A ^ B));
endmodule 

module Nhan4Bit(A, B, S);
    input  [3:0] A, B;
    output [7:0] S;

    wire pp00, pp01, pp02, pp03;
    wire pp10, pp11, pp12, pp13;
    wire pp20, pp21, pp22, pp23;
    wire pp30, pp31, pp32, pp33;

    assign pp00 = A[0] & B[0];
    assign pp01 = A[1] & B[0];
    assign pp02 = A[2] & B[0];
    assign pp03 = A[3] & B[0];

    assign pp10 = A[0] & B[1];
    assign pp11 = A[1] & B[1];
    assign pp12 = A[2] & B[1];
    assign pp13 = A[3] & B[1];

    assign pp20 = A[0] & B[2];
    assign pp21 = A[1] & B[2];
    assign pp22 = A[2] & B[2];
    assign pp23 = A[3] & B[2];

    assign pp30 = A[0] & B[3];
    assign pp31 = A[1] & B[3];
    assign pp32 = A[2] & B[3];
    assign pp33 = A[3] & B[3];

    assign S[0] = pp00;

    wire s1, c1;
    HA HA1 (.A(pp01), .B(pp10), .Sum(s1), .Carry(c1));
    assign S[1] = s1;

    wire s_fa1, c_fa1;
    FA FA1 (.A(pp02), .B(pp11), .Cin(pp20), .Sum(s_fa1), .Cout(c_fa1));
    wire s2, c2;
    HA HA2 (.A(s_fa1), .B(c1), .Sum(s2), .Carry(c2));
    assign S[2] = s2;

    wire s_fa2, c_fa2;
    FA FA2 (.A(pp03), .B(pp12), .Cin(pp21), .Sum(s_fa2), .Cout(c_fa2));

    wire s_fa3, c_fa3;
    FA FA3 (.A(pp30), .B(c_fa1), .Cin(c2), .Sum(s_fa3), .Cout(c_fa3));

    wire s3, c3;
    HA HA3 (.A(s_fa2), .B(s_fa3), .Sum(s3), .Carry(c3));
    assign S[3] = s3;

    wire s_fa4, c_fa4;
    FA FA4 (.A(pp13), .B(pp22), .Cin(pp31), .Sum(s_fa4), .Cout(c_fa4));

    wire s_fa5, c_fa5;
    FA FA5 (.A(c_fa2), .B(c_fa3), .Cin(c3), .Sum(s_fa5), .Cout(c_fa5));

    wire s4, c4;
    HA HA4 (.A(s_fa4), .B(s_fa5), .Sum(s4), .Carry(c4));
    assign S[4] = s4;

    wire s_fa6, c_fa6;
    FA FA6 (.A(pp23), .B(pp32), .Cin(c_fa4), .Sum(s_fa6), .Cout(c_fa6));

    wire s5, c5;
    FA FA7 (.A(c_fa5), .B(c4), .Cin(s_fa6), .Sum(s5), .Cout(c5));
    assign S[5] = s5;

    wire s6, c6;
    FA FA8 (.A(pp33), .B(c_fa6), .Cin(c5), .Sum(s6), .Cout(c6));
    assign S[6] = s6;

    assign S[7] = c6;

endmodule

module Lab4_b2(HEX2, HEX1, HEX0, A, B, S);
    input  [3:0] A, B;
    output [7:0] S;
    output [0:6] HEX2, HEX1, HEX0;

    wire [3:0] donvi, chuc, tram;

    Nhan4Bit mult(.A(A), .B(B), .S(S));
    assign tram = S/7'b1100100;
    assign chuc = S/4'b1010 - tram*4'b1010;
    assign donvi = S - (tram*7'b1100100) - (chuc*4'b1010);

    assign HEX0 = (donvi == 4'b0000) ? 7'b0000001 :
                  (donvi == 4'b0001) ? 7'b1001111 :
                  (donvi == 4'b0010) ? 7'b0010010 :
                  (donvi == 4'b0011) ? 7'b0000110 :
                  (donvi == 4'b0100) ? 7'b1001100 :
                  (donvi == 4'b0101) ? 7'b0100100 :
                  (donvi == 4'b0110) ? 7'b0100000 :
                  (donvi == 4'b0111) ? 7'b0001111 :
                  (donvi == 4'b1000) ? 7'b0000000 :
                  (donvi == 4'b1001) ? 7'b0000100 :
                  7'b0000001;

    assign HEX1 = (chuc == 4'b0000) ? 7'b0000001 :
                  (chuc == 4'b0001) ? 7'b1001111 :
                  (chuc == 4'b0010) ? 7'b0010010 :
                  (chuc == 4'b0011) ? 7'b0000110 :
                  (chuc == 4'b0100) ? 7'b1001100 :
                  (chuc == 4'b0101) ? 7'b0100100 :
                  (chuc == 4'b0110) ? 7'b0100000 :
                  (chuc == 4'b0111) ? 7'b0001111 :
                  (chuc == 4'b1000) ? 7'b0000000 :
                  (chuc == 4'b1001) ? 7'b0000100 :
                  7'b0000001;

    assign HEX2 = (tram == 4'b0000) ? 7'b0000001 :
                  (tram == 4'b0001) ? 7'b1001111 :
                  (tram == 4'b0010) ? 7'b0010010 :
                  (tram == 4'b0011) ? 7'b0000110 :
                  (tram == 4'b0100) ? 7'b1001100 :
                  (tram == 4'b0101) ? 7'b0100100 :
                  (tram == 4'b0110) ? 7'b0100000 :
                  (tram == 4'b0111) ? 7'b0001111 :
                  (tram == 4'b1000) ? 7'b0000000 :
                  (tram == 4'b1001) ? 7'b0000100 :
                  7'b0000001;
endmodule
