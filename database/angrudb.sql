
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
-- id uuid NOT NULL DEFAULT uuid_generate_v5(uuid_ns_url(), (uuid_generate_v4())::text),


-- Table: public.users

-- DROP TABLE public.users;

CREATE TABLE public.users
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  first_name character varying(255),
  middle_name character varying(255),
  last_name character varying(255),
  username character varying(255) NOT NULL,
  email character varying(255) NOT NULL,
  password character varying(255) NOT NULL,
  type integer NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT users_pkey PRIMARY KEY (id),
  CONSTRAINT users_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_ukey_email UNIQUE (email),
  CONSTRAINT users_ukey_username UNIQUE (username)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.users
  OWNER TO masoud;


INSERT INTO public.users(
            id, first_name, middle_name, last_name, username, email, password, 
            type, created_by, deleted_by, updated_by, created_at, deleted_at, 
            updated_at, details, status, situation, description)
    VALUES (Default, 'zeus', 'G', 'god', 'zeus', 'zeus@olympus.god', '7c4a8d09ca3762af61e59520943dc26494f8941b',
            0, NULL, NULL, NULL, now(), NULL,
            NULL, '{}', 1, 1, 'Zeus is the sky and thunder god in ancient Greek religion, who rules as king of the gods of Mount Olympus. His name is cognate with the first element of his Roman equivalent Jupiter. His mythologies and powers are similar, though not identical, to those of Indo-European deities such as Indra, Jupiter, Perkūnas, Perun, and Thor');


-- Table: public.security_roles

-- DROP TABLE public.security_roles;

CREATE TABLE public.security_roles
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT security_roles_pkey PRIMARY KEY (id),
  CONSTRAINT security_roles_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT security_roles_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT security_roles_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT security_roles_ukey_name UNIQUE (name)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.security_roles
  OWNER TO masoud;


INSERT INTO public.security_roles(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, status, situation, description)
    VALUES (DEFAULT, 'uploader', 'uploader', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 1, 0, '');

INSERT INTO public.security_roles(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, status, situation, description)
    VALUES (DEFAULT, 'reporter', 'reporter', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 1, 0, '');


-- Table: public.users_security_roles

-- DROP TABLE public.users_security_roles;

CREATE TABLE public.users_security_roles
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  _user_ uuid NOT NULL,
  security_role uuid NOT NULL,  
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT users_security_roles_pkey PRIMARY KEY (id),
  CONSTRAINT users_security_roles_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_security_roles_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_security_roles__user__fkey FOREIGN KEY (_user_)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_security_roles_security_role_fkey FOREIGN KEY (security_role)
      REFERENCES public.security_roles (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_security_roles_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.users_security_roles
  OWNER TO masoud;



-- Table: public.entities

-- DROP TABLE public.entities;

CREATE TABLE public.entities
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  type integer NOT NULL,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT entities_pkey PRIMARY KEY (id),
  CONSTRAINT entities_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT entities_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT entities_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT entities_ukey_name UNIQUE (name)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.entities
  OWNER TO masoud;


INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'aggrigators', 'aggrigators', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'entities', 'entities', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'mobile_operators', 'mobile_operators', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'privileges', 'privileges', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'security_roles', 'security_roles', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'users', 'users', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'users_security_roles', 'users_security_roles', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at, 
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'content_providers', 'content_providers', (select id from users where username='zeus'), NULL, NULL, NOW(), 
            NULL, NULL, 0, 1, 0, '');


-- Table: public.privileges

-- DROP TABLE public.privileges;

CREATE TABLE public.privileges
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  security_role uuid NOT NULL,
  entity uuid NOT NULL,
  privilege_string character varying(255),  
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT privileges_pkey PRIMARY KEY (id),
  CONSTRAINT privileges_security_role_fkey FOREIGN KEY (security_role)
      REFERENCES public.security_roles (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT privileges_entity_fkey FOREIGN KEY (entity)
      REFERENCES public.entities (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,    
  CONSTRAINT privileges_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT privileges_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT privileges_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.privileges
  OWNER TO masoud;

---------------------------------------------------------------------------------------------------------------------

-- Table: public.mobile_operators

-- DROP TABLE public.mobile_operators;

CREATE TABLE public.mobile_operators
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
  code character varying(255),
  phone character varying(255),
  email character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT mobile_operators_pkey PRIMARY KEY (id),
  CONSTRAINT mobile_operators_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT mobile_operators_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT mobile_operators_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.mobile_operators
  OWNER TO masoud;


-- Table: public.aggrigators

-- DROP TABLE public.aggrigators;

CREATE TABLE public.aggrigators
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
  code character varying(255),
  phone character varying(255),
  email character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT aggrigators_pkey PRIMARY KEY (id),
  CONSTRAINT users_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.aggrigators
  OWNER TO masoud;


-- Table: public.content_providers

-- DROP TABLE public.content_providers;

CREATE TABLE public.content_providers
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  admin uuid,
  name character varying(255) NOT NULL,
  title character varying(255),
  code character varying(255),
  phone character varying(255),
  email character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT content_providers_pkey PRIMARY KEY (id),
  CONSTRAINT content_providers_admin_fkey FOREIGN KEY (admin)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT content_providers_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT content_providers_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT content_providers_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.content_providers
  OWNER TO masoud;



-- Table: public.services

-- DROP TABLE public.services;

CREATE TABLE public.services
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  pendar uuid,
  mobile_operator uuid,
  aggrigator uuid,
  content_provider uuid,
  name character varying(255) NOT NULL,
  title character varying(255),
  code character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT services_pkey PRIMARY KEY (id),
  CONSTRAINT services_mobile_operator_fkey FOREIGN KEY (mobile_operator)
      REFERENCES public.mobile_operators (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT services_aggrigator_fkey FOREIGN KEY (aggrigator)
      REFERENCES public.aggrigators (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT services_content_provider_fkey FOREIGN KEY (content_provider)
      REFERENCES public.content_providers (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT services_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT services_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT services_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT services_ukey_pendar UNIQUE (pendar)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.services
  OWNER TO masoud;


-- Table: public.members

-- DROP TABLE public.members;

CREATE TABLE public.members
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),  
  phone character varying(255),
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT members_pkey PRIMARY KEY (id),
  CONSTRAINT members_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT members_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT members_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.members
  OWNER TO masoud;


-- Table: public.subscriptions

-- DROP TABLE public.subscriptions;

CREATE TABLE public.subscriptions
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),  
  member uuid NOT NULL,
  service uuid NOT NULL,
  last_login timestamp with time zone,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  details json,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT subscriptions_pkey PRIMARY KEY (id),
  CONSTRAINT subscriptions_member_fkey FOREIGN KEY (member)
      REFERENCES public.members (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT subscriptions_service_fkey FOREIGN KEY (service)
      REFERENCES public.services (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT subscriptions_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT subscriptions_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT subscriptions_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.subscriptions
  OWNER TO masoud;







