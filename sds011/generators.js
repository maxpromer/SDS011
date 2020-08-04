Blockly.JavaScript['sds011'] = function (block) {
	var dropdown_pin = block.getFieldValue('pin');
	var dropdown_type = block.getFieldValue('type');
	var code = `DEV_IO.SDS011(${dropdown_pin}).get(${dropdown_type})`;
	return [code, Blockly.JavaScript.ORDER_NONE];
};
