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
			$value = $item->info['name'];
			
			//Is theme enabled?
			if($item->status){
				$themesArray[$key] = $value;
			}

		}
		//print_r($themNames['splashme']->info['name']);
		//Create new array to hold form elements
		$form = array();

		//Add an auto-complete field to the array
		$form['splash_me_node_lookup'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Node Title or ID'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_node_lookup'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("Title or ID of the node to be used as splash screen."),
			//Whether the field is required
			'#required' => TRUE,
			//The url to trigger the callback function
			'#autocomplete_path' => 'splash-me-node-results'

		);

		$form['splash_me_continue_link'] = array (

			'#type' => 'checkbox',
			'#title' => t('Add a continue link'),
			'#description' => t('Adds a Continue Link to the splash page node.'),
			'#default_value' => variable_get('splash_me_continue_link', 0),
			'#required' => FALSE

		);

		//Add an auto-complete field to the array
		$form['splash_me_continue_link_text'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Continue link text'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_continue_link_text'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("Text to be used in the continue link."),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_continue_link"]' => array('checked' => TRUE),
			    )
			)

		);

		$form['splash_me_continue_url'] = array (

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('URL for the continue link'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_continue_url'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("URL to be used in the continue link i.e. /node/123."),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_continue_link"]' => array('checked' => TRUE),
			    )
			)

		);

		$form['splash_me_themes'] = array (

			'#type' => 'select',
			'#options' => $themesArray,
			'#title' => 'Splash page theme',
			'#description' => 'Select a theme to use for the splash page',
			'#default_value' => variable_get('splash_me_themes'),
			'#required' => FALSE

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


	//Validation for the configuration form
	function splash_me_admin_validate($form, &$form_state) {
	 
		$continueOption = $form_state['values']['splash_me_continue_link'];
		$continueText = $form_state['values']['splash_me_continue_link_text'];
		$continueUrl = $form_state['values']['splash_me_continue_url'];
		
		//If checkbox is checked but  URL empty
		if($continueOption && !$continueUrl) {

			$errMsg = 'URL for the continue link is required';

			form_set_error('emptyContinueUrl', $errMsg);

		}

		//If checkbox is checked but continue text empty
		if($continueOption && !$continueText) {

			$errMsg = 'Text for the continue link is required';

			form_set_error('emptyContinueText', $errMsg);

		}

	}


