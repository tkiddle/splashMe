<?php 

	/**
	 *@file
	 *splash_me.admin.inc
	 */

	//Create the admin configuration form
	



	function splash_me_admin() {
	
		$themNames = list_themes($refresh = FALSE);
		$themesArray = array('default' => '--select a theme--');
		
		foreach ($themNames as $item) {

			$key = $item->name;
			$value = $item->name;

			$themesArray[$key] = $value;
		}
		
		//Create new array to hold form elements
		$form = array();

		//Add an auto-complete field to the array
		$form['splash_me_node_lookup'] = array(
			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Node Title or ID'),
			//Get the value from the DB else use ) which is the default
			'#default_value' => variable_get('splash_me_node_lookup', 1),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("Title or ID of the node to be used as splash screen."),
			//Whether the field is required
			'#required' => FALSE,
			//The url to trigger the callback function
			'#autocomplete_path' => 'splash-me-node-results',
		); 

		$form['splash_me_themes'] = array (

			'#type' => 'select',
			'#options' => $themesArray,
			'#title' => 'Splash page theme',
			'#description' => 'Select a theme to use for the splash page',
			'#default_value' => variable_get('splash_me_themes'),
			'#required' => FALSE,

		);

		unset($themesArray);


		$form['splash_me_redirect_time'] = array(
			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Redirect time'),
			//Get the value from the DB else use 20 which is the default
			'#default_value' => variable_get('splash_me_redirect_time', 20),
			//HTML input width
			'#size' => 3,
			//Max length of chars
			'#maxlength' => 6,
			//Description of the field
			'#description' => t("The time it takes to redirect back to the homepage in seconds."),
			//Whether the field is required
			'#required' => FALSE
		);

		//Once the form is built return it passing the $form array
		return system_settings_form($form);
	  
	}