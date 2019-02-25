
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

INSERT INTO public.security_roles(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, status, situation, description)
    VALUES (DEFAULT, 'security manager', 'manage security permissions privilege', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 1, 0, '');

INSERT INTO public.security_roles(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, status, situation, description)
    VALUES (DEFAULT, 'service manager', 'manage service and related', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 1, 0, '');

INSERT INTO public.security_roles(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, status, situation, description)
    VALUES (DEFAULT, 'content manager', 'upload and manage content', (select id from users where username='zeus'), NULL, NULL, NOW(),
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


INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'mobile_operators', 'mobile_operators', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'aggrigators', 'aggrigators', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'content_providers', 'content_providers', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'services', 'services', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'members', 'members', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'subscriptions', 'subscriptions', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'channels', 'channels', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'playlists', 'playlists', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'publishers', 'publishers', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'contents', 'contents', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'videos', 'videos', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'comments', 'comments', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'playlists_contents', 'playlists_contents', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'rates', 'rates', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'tags', 'tags', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'tags_channels', 'tags_channels', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'tags_contents', 'tags_contents', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'tags_playlists', 'tags_playlists', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'users_content_providers', 'users_content_providers', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'users_publishers', 'users_publishers', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'users', 'users', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'security_roles', 'security_roles', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'users_security_roles', 'users_security_roles', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'entities', 'entities', (select id from users where username='zeus'), NULL, NULL, NOW(),
            NULL, NULL, 0, 1, 0, '');

INSERT INTO public.entities(
            id, name, title, created_by, deleted_by, updated_by, created_at,
            deleted_at, updated_at, type, status, situation, description)
    VALUES (DEFAULT, 'privileges', 'privileges', (select id from users where username='zeus'), NULL, NULL, NOW(),
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
  CONSTRAINT aggrigators_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT aggrigators_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT aggrigators_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

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

-- Table: public.channels

-- DROP TABLE public.channels;

CREATE TABLE public.channels
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
  service uuid NOT NULL,
  parent uuid,
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
  CONSTRAINT channels_pkey PRIMARY KEY (id),
  CONSTRAINT channels_service_fkey FOREIGN KEY (service)
      REFERENCES public.services (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT channels_parent_fkey FOREIGN KEY (parent)
      REFERENCES public.channels (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT channels_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT channels_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT channels_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.playlists

-- DROP TABLE public.playlists;

CREATE TABLE public.playlists
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
  service uuid NOT NULL,
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
  CONSTRAINT playlists_pkey PRIMARY KEY (id),
  CONSTRAINT playlists_service_fkey FOREIGN KEY (service)
      REFERENCES public.services (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.publishers

-- DROP TABLE public.publishers;

CREATE TABLE public.publishers
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
  CONSTRAINT publishers_pkey PRIMARY KEY (id),
  CONSTRAINT publishers_admin_fkey FOREIGN KEY (admin)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT publishers_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT publishers_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT publishers_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.users_content_providers

-- DROP TABLE public.users_content_providers;

CREATE TABLE public.users_content_providers
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  _user_ uuid NOT NULL,
  content_provider uuid NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT users_content_providers_pkey PRIMARY KEY (id),
  CONSTRAINT users_content_providers__user__fkey FOREIGN KEY (_user_)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_content_providers_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_content_providers_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_content_providers_content_provider_fkey FOREIGN KEY (content_provider)
      REFERENCES public.content_providers (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_content_providers_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.users_publishers

-- DROP TABLE public.users_publishers;

CREATE TABLE public.users_publishers
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  _user_ uuid NOT NULL,
  publisher uuid NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT users_publishers_pkey PRIMARY KEY (id),
  CONSTRAINT users_publishers__user__fkey FOREIGN KEY (_user_)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_publishers_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_publishers_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_publishers_publisher_fkey FOREIGN KEY (publisher)
      REFERENCES public.publishers (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT users_publishers_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.contents

-- DROP TABLE public.contents;

CREATE TABLE public.contents
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  service uuid NOT NULL,
  publisher uuid,
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
  CONSTRAINT contents_pkey PRIMARY KEY (id),
  CONSTRAINT contents_service_fkey FOREIGN KEY (service)
      REFERENCES public.services (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT contents_publisher_fkey FOREIGN KEY (publisher)
      REFERENCES public.publishers (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT contents_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT contents_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT contents_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.playlists_contents

-- DROP TABLE public.playlists_contents;

CREATE TABLE public.playlists_contents
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  playlist uuid NOT NULL,
  content uuid NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT playlists_contents_pkey PRIMARY KEY (id),
  CONSTRAINT playlists_contents_playlist_fkey FOREIGN KEY (playlist)
      REFERENCES public.playlists (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_contents_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_contents_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_contents_content_fkey FOREIGN KEY (content)
      REFERENCES public.contents (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT playlists_contents_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);


-- Table: public.contents

-- DROP TABLE public.contents;

CREATE TABLE public.tags
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  name character varying(255) NOT NULL,
  title character varying(255),
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
  CONSTRAINT tags_pkey PRIMARY KEY (id),
  CONSTRAINT tags_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_ukey_name UNIQUE (name)
)
WITH (
  OIDS=FALSE
);

-- Table: public.videos

-- DROP TABLE public.videos;

CREATE TABLE public.videos
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  content uuid NOT NULL,
  name character varying(255),
  title character varying(255),
  path character varying(255),
  size numeric,
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
  CONSTRAINT videos_pkey PRIMARY KEY (id),
  CONSTRAINT videos_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT videos_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT videos_content_fkey FOREIGN KEY (content)
      REFERENCES public.contents (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT videos_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);


-- Table: public.tags_contents

-- DROP TABLE public.tags_contents;

CREATE TABLE public.tags_contents
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  tag uuid NOT NULL,
  content uuid NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT tags_contents_pkey PRIMARY KEY (id),
  CONSTRAINT tags_contents_tag_fkey FOREIGN KEY (tag)
      REFERENCES public.tags (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_contents_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_contents_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_contents_content_fkey FOREIGN KEY (content)
      REFERENCES public.contents (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_contents_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.tags_playlists

-- DROP TABLE public.tags_playlists;

CREATE TABLE public.tags_playlists
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  tag uuid NOT NULL,
  playlist uuid NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT tags_playlists_pkey PRIMARY KEY (id),
  CONSTRAINT tags_playlists_tag_fkey FOREIGN KEY (tag)
      REFERENCES public.tags (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_playlists_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_playlists_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_playlists_playlist_fkey FOREIGN KEY (playlist)
      REFERENCES public.playlists (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_playlists_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);

-- Table: public.tags_channels

-- DROP TABLE public.tags_channels;

CREATE TABLE public.tags_channels
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  tag uuid NOT NULL,
  channel uuid NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT tags_channels_pkey PRIMARY KEY (id),
  CONSTRAINT tags_channels_tag_fkey FOREIGN KEY (tag)
      REFERENCES public.tags (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_channels_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_channels_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_channels_channel_fkey FOREIGN KEY (channel)
      REFERENCES public.channels (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT tags_channels_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);


-- Table: public.comments

-- DROP TABLE public.comments;

CREATE TABLE public.comments
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  member uuid NOT NULL,
  content uuid NOT NULL,
  comment character varying(255),
  reply_to uuid,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT comments_pkey PRIMARY KEY (id),
  CONSTRAINT comments_member_fkey FOREIGN KEY (member)
      REFERENCES public.members (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT comments_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT comments_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT comments_content_fkey FOREIGN KEY (content)
      REFERENCES public.contents (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT comments_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT comments_reply_to_fkey FOREIGN KEY (reply_to)
      REFERENCES public.comments (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);


-- Table: public.rates

-- DROP TABLE public.rates;

CREATE TABLE public.rates
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  member uuid NOT NULL,
  content uuid NOT NULL,
  rate integer NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT rates_pkey PRIMARY KEY (id),
  CONSTRAINT rates_content_fkey FOREIGN KEY (content)
      REFERENCES public.contents (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT rates_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT rates_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT rates_member_fkey FOREIGN KEY (member)
      REFERENCES public.members (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT rates_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);


-- Table: public.attractions

-- DROP TABLE public.attractions;

CREATE TABLE public.attractions
(
  id uuid NOT NULL DEFAULT uuid_generate_v4(),
  member uuid NOT NULL,
  content uuid NOT NULL,
  attraction integer NOT NULL,
  created_by uuid,
  deleted_by uuid,
  updated_by uuid,
  created_at timestamp with time zone,
  deleted_at timestamp with time zone,
  updated_at timestamp with time zone,
  status integer NOT NULL,
  situation integer NOT NULL,
  description character varying,
  CONSTRAINT attractions_pkey PRIMARY KEY (id),
  CONSTRAINT attractions_content_fkey FOREIGN KEY (content)
      REFERENCES public.contents (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT attractions_created_by_fkey FOREIGN KEY (created_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT attractions_deleted_by_fkey FOREIGN KEY (deleted_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT attractions_member_fkey FOREIGN KEY (member)
      REFERENCES public.members (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT attractions_updated_by_fkey FOREIGN KEY (updated_by)
      REFERENCES public.users (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
)
WITH (
  OIDS=FALSE
);
