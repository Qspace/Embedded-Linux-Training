#include <mysql.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>



/// Prints out a MySQL error message and exits

///

/// This function should be called after a MySQL error has been encountered.  This function will then

/// notify the user of the error that has occurred, clean up the existing MySQL connection, and then

/// exit the program.

///

/// @param The MySQL connection to clean up before exiting

void error_exit(MYSQL *con)

{

	fprintf(stderr, "%s\n", mysql_error(con));



	if (con != NULL)

	{

		mysql_close(con);

	}



	exit(1);

}



int main(int argc, const char *argv[])

{

	// Initialize a connection to MySQL

	MYSQL *con = mysql_init(NULL);

	if(con == NULL)

	{

		error_exit(con);

	}



	// Connect to MySQL

	// Here we pass in:

	//  host name => localhost

	//  user name => pi

	//  password => pi

	//  database name => TempDB

	if (mysql_real_connect(con, "localhost", "pi", "pi", "TempDB", 0, NULL, 0) == NULL)

	{

		error_exit(con);

	}



	// Create the TempMeas database (if it doesn't already exist)

	if (mysql_query(con, "CREATE TABLE IF NOT EXISTS TempMeas(MeasTime DATETIME, Temp DOUBLE)"))

	{

		error_exit(con);

	}



	// Initialize a MySQL statement

	MYSQL_STMT *stmt = mysql_stmt_init(con);

	if (stmt == NULL)

	{

		error_exit(con);

	}



	// Set out insert query as the MySQL statement

	const char *query = "INSERT INTO TempMeas(MeasTime, Temp) VALUES(NOW(), ?)";

	if (mysql_stmt_prepare(stmt, query, strlen(query)))

	{

		error_exit(con);

	}



	// Create the MySQL bind structure to store the data that we are going to insert

	double temp = 0.0;

	MYSQL_BIND bind;

	memset(&bind, 0, sizeof(bind));

	bind.buffer_type = MYSQL_TYPE_DOUBLE;

	bind.buffer = (char *)&temp;

	bind.buffer_length = sizeof(double);



	// Bind the data structure to the MySQL statement

	if (mysql_stmt_bind_param(stmt, &bind))

	{

		error_exit(con);

	}



	// Insert multiple records into the database,

	// with different data each time

	for (int i = 0; i < 10; i++)

	{

		temp = (float)i;

		mysql_stmt_execute(stmt);

	}



	// Close the MySQL connection

	mysql_close(con);



	return 0;

}
