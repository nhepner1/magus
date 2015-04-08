<form method="post" action="<?php print $_SERVER['PHP_SELF']; ?>">
<table class="login">
	<tr>
    	<th class="grey_3" colspan="2" bgcolor="#eeeeee">Login</th>
	</tr>
	<tr>
	    <td>Username:</td>
	    <td><input type="text" id="username" name="username" value="" /></td>

	</tr>
	<tr>
	    <td>Password:</td>
	    <td><input type="password" id="password" name="password" /></td>
	</tr>
	<tr>
	    <td class="grey_3" colspan="2" ><input value="Login" id="doLogin" name="doLogin" type="submit" /></td>
	</tr>
</table>
</form>
