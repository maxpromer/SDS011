Blockly.Blocks['sds011'] = {
	init: function () {
		this.jsonInit({
			"type": "sds011",
			"message0": Blockly.Msg.SDS011_MESSAGE,
			"args0": [
				{
					"type": "field_dropdown",
					"name": "pin",
					"options": [
						[
							"IN1",
							"32"
						],
						[
							"IN2",
							"33"
						],
						[
							"IN3",
							"34"
						],
						[
							"IN4",
							"35"
						],
						[
							"OUT1",
							"26"
						],
						[
							"OUT2",
							"27"
						],
						[
							"23",
							"23"
						],
						[
							"19",
							"19"
						],
						[
							"18",
							"18"
						]
					]
				},
				{
					"type": "field_dropdown",
					"name": "type",
					"options": [
						[
							"PM2.5",
							"1"
						],
						[
							"PM10",
							"2"
						]
					]
				}
			],
			"output": "Number",
			"colour": 195,
			"tooltip": Blockly.Msg.SDS011_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	}
};
