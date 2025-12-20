module Lab5_b4(
    input  wire        CLOCK_50,
    output reg [9:0]   LEDR
);

reg [23:0] counter;
reg moving_left;

initial begin
    counter     = 0;
    LEDR        = 10'b1000000000;
    moving_left = 0;
end

always @(posedge CLOCK_50) begin
    counter <= counter + 1;

    if (counter == 0) begin
        // Trường hợp 1: Chạm cạnh phải -> Đổi hướng sang Trái và dịch luôn
        if (LEDR == 10'b0000000001) begin
            moving_left <= 1;
            LEDR <= LEDR << 1; 
        end
        // Trường hợp 2: Chạm cạnh trái -> Đổi hướng sang Phải và dịch luôn
        else if (LEDR == 10'b1000000000) begin
            moving_left <= 0;
            LEDR <= LEDR >> 1;
        end
        // Trường hợp 3: Đang ở giữa -> Đi theo hướng hiện tại
        else begin
            if (moving_left) LEDR <= LEDR << 1;
            else             LEDR <= LEDR >> 1;
        end
    end
end

endmodule