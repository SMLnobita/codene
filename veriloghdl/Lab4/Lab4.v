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

module Add4Bit(A, B, S);
    input  [3:0] A, B;
    output [4:0] S;

    wire c1, c2, c3;
    HA U0 (.A(A[0]), .B(B[0]), .Sum(S[0]), .Carry(c1));
    FA U1 (.A(A[1]), .B(B[1]), .Cin(c1), .Sum(S[1]), .Cout(c2));
    FA U2 (.A(A[2]), .B(B[2]), .Cin(c2), .Sum(S[2]), .Cout(c3));
    FA U3 (.A(A[3]), .B(B[3]), .Cin(c3), .Sum(S[3]), .Cout(S[4]));
endmodule

module Lab4(HEX1, HEX0, A, B, S);
	input [3:0] A, B;
	output [4:0] S;
	output [0:6] HEX1, HEX0;
    wire [3:0] donvi, chuc;
    
    Add4Bit adder(.A(A), .B(B), .S(S));
    assign chuc = S/4'b1010;
    assign donvi = S - chuc*4'b1010;
    assign HEX0 = (donvi == 4'b0000) ? 7'b0000001 : //0
                  (donvi == 4'b0001) ? 7'b1001111 : //1
                  (donvi == 4'b0010) ? 7'b0010010 : //2
                  (donvi == 4'b0011) ? 7'b0000110 : //3
                  (donvi == 4'b0100) ? 7'b1001100 : //4
                  (donvi == 4'b0101) ? 7'b0100100 : //5
                  (donvi == 4'b0110) ? 7'b0100000 : //6
                  (donvi == 4'b0111) ? 7'b0001111 : //7
                  (donvi == 4'b1000) ? 7'b0000000 : //8
                  (donvi == 4'b1001) ? 7'b0000100 : //9
                  7'b0000001;
    assign HEX1 = (chuc == 4'b0000) ? 7'b0000001 : //0
                  (chuc == 4'b0001) ? 7'b1001111 : //1
                  (chuc == 4'b0010) ? 7'b0010010 : //2
                  (chuc == 4'b0011) ? 7'b0000110 : //3
                  (chuc == 4'b0100) ? 7'b1001100 : //4
                  (chuc == 4'b0101) ? 7'b0100100 : //5
                  (chuc == 4'b0110) ? 7'b0100000 : //6
                  (chuc == 4'b0111) ? 7'b0001111 : //7
                  (chuc == 4'b1000) ? 7'b0000000 : //8
                  (chuc == 4'b1001) ? 7'b0000100 : //9
                  7'b0000001;
endmodule