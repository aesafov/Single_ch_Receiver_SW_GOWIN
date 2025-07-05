module Top_module
(
    input clkin,
    input signal_in,
    input key1_n,
    input key2_n,
    output uart0_txd,
    output led    
    
);
    wire [15:0]gpioin;
    wire [15:0] data;
    wire [15:0]gpioout;
    assign led  = gpioout[15];
    //assign led  = front;
    
    Gowin_PLLVR_PLL_100MGz PLL_100MGz(
        .clkout(clkout_100MGz), //output clkout
        .clkin(clkin) //input clkin
    );

    Gowin_PLLVR_PLL_78MGz PLL_78MGz(
        .clkout(clkout_78MGz), //output clkout
        .clkin(clkin) //input clkin
    );

    manchester inst_manchester 
    (
        .CLK(clkout_100MGz),
        .signal_in(signal_in),
        .data(data),
        .front(front),
        .not_work(not_work)
    );

    //assign gpioin = {not_work, front, data};
    assign gpioin[11:0] = data[11:0];
    assign gpioin[12] = front;
    assign gpioin[13] = not_work;

	Gowin_EMPU_Top core_Cortex
    (
		.sys_clk(clkout_78MGz), //input sys_clk
		.gpioin(gpioin), //input [15:0] gpioin
		.gpioout(gpioout), //output [15:0] gpioout
		.gpioouten(gpioouten), //output [15:0] gpioouten
		.uart0_txd(uart0_txd), //output uart0_txd
		.reset_n(key2_n) //input reset_n
	);


endmodule