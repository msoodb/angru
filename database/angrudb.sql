
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



