module cau2b(
    input wire CLOCK_50,
    input wire [0:0] KEY,
    input wire [1:0] SW,
    output reg [6:0] HEX5, HEX4, HEX3, HEX2, HEX1, HEX0
)