module Lab5_b3(
    input  wire       CLOCK_50,
    output reg [9:0]  LEDR
);

reg [25:0] counter;

initial begin
    counter = 0;
    LEDR    = 10'b1000000000;
end

always @(posedge CLOCK_50) begin
    counter <= counter + 1;

    if (counter == 0) begin
        if (LEDR == 10'b0000000001)
            LEDR <= 10'b1000000000;
        else
            LEDR <= LEDR >> 1;
    end
end

endmodule