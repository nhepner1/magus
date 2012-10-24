<html>
<head>
<title><?php echo $title; ?></title>
<link rel="stylesheet" type="text/css" href="themes/default/style.css" />
</head>
<body>
<div class="outerwrapper">
	<div class="header">
		<div class="logo"><?php echo $header; ?></div>
		<?php if(isset($top_menu)): ?> 
			<div class="top_menu"><?php echo $top_menu; ?></div>
		<?php endif; ?>
		<div class="clear"></div>
	</div>

	<div class="wrapper">
		
		<?php if(isset($left_sidebar)): ?>
		<div class="left_sidebar"><?php echo $left_sidebar; ?></div>
		<?php endif; ?>
		
		<?php if(isset($content)): ?>
		<div class="content"><?php echo $content; ?></div>
		<?php endif; ?>
		
		<?php if(isset($right_sidebar)): ?>
		<div class="right_sidebar"><?php echo $right_sidebar; ?></div>
		<?php endif; ?>
	<div class='clear'></div>
	</div>
	<div class="footer">
		<div class="footer_links"><?php echo $footer; ?></div>
	</div>
</div>
</body>
</html>