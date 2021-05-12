-- Database: otlodbc

-- DROP DATABASE otlodbc;

CREATE DATABASE otlodbc
    WITH 
    OWNER = postgres
    ENCODING = 'UTF8'
    LC_COLLATE = 'C.UTF-8'
    LC_CTYPE = 'C.UTF-8'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1;

COMMENT ON DATABASE otlodbc
    IS 'otl4 for odbc';
    
-- SCHEMA: otluser

-- DROP SCHEMA otluser ;

CREATE SCHEMA otluser
    AUTHORIZATION postgres;
    
    
-- Table: otluser.company

-- DROP TABLE otluser.company;

CREATE TABLE otluser.company
(
	    id integer NOT NULL,
	    name character varying(20) COLLATE pg_catalog."default" NOT NULL,
	    age integer NOT NULL,
	    address character(25) COLLATE pg_catalog."default",
	    salary numeric(18,2),
	    CONSTRAINT company_pkey PRIMARY KEY (id)
)
WITH (
	    OIDS = FALSE
)
TABLESPACE pg_default;

ALTER TABLE otluser.company
    OWNER to postgres;
    
INSERT INTO otluser.COMPANY (ID,NAME,AGE,ADDRESS,SALARY) VALUES (1, 'Paul', 32, 'California', 20000.00);
