--
-- PostgreSQL database dump
--

-- Dumped from database version 9.6.10
-- Dumped by pg_dump version 9.6.10

-- Started on 2019-02-24 11:48:24 +0330

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 2 (class 3079 OID 16758)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2620 (class 0 OID 0)
-- Dependencies: 2
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- TOC entry 1 (class 3079 OID 24586)
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- TOC entry 2621 (class 0 OID 0)
-- Dependencies: 1
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


--
-- TOC entry 4 (class 3079 OID 16763)
-- Name: hstore; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS hstore WITH SCHEMA public;


--
-- TOC entry 2622 (class 0 OID 0)
-- Dependencies: 4
-- Name: EXTENSION hstore; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION hstore IS 'data type for storing sets of (key, value) pairs';


--
-- TOC entry 3 (class 3079 OID 25702)
-- Name: uuid-ossp; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS "uuid-ossp" WITH SCHEMA public;


--
-- TOC entry 2623 (class 0 OID 0)
-- Dependencies: 3
-- Name: EXTENSION "uuid-ossp"; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION "uuid-ossp" IS 'generate universally unique identifiers (UUIDs)';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 194 (class 1259 OID 26005)
-- Name: aggrigators; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.aggrigators (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.aggrigators OWNER TO masoud;

--
-- TOC entry 218 (class 1259 OID 35093)
-- Name: attractions; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.attractions (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.attractions OWNER TO masoud;

--
-- TOC entry 204 (class 1259 OID 34566)
-- Name: channels; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.channels (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.channels OWNER TO masoud;

--
-- TOC entry 216 (class 1259 OID 35020)
-- Name: comments; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.comments (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.comments OWNER TO masoud;

--
-- TOC entry 200 (class 1259 OID 26342)
-- Name: content_providers; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.content_providers (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.content_providers OWNER TO masoud;

--
-- TOC entry 192 (class 1259 OID 25574)
-- Name: content_providers_id_seq; Type: SEQUENCE; Schema: public; Owner: angru
--

CREATE SEQUENCE public.content_providers_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.content_providers_id_seq OWNER TO angru;

--
-- TOC entry 209 (class 1259 OID 34760)
-- Name: contents; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.contents (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.contents OWNER TO masoud;

--
-- TOC entry 198 (class 1259 OID 26258)
-- Name: entities; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.entities (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.entities OWNER TO masoud;

--
-- TOC entry 202 (class 1259 OID 26418)
-- Name: members; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.members (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.members OWNER TO masoud;

--
-- TOC entry 195 (class 1259 OID 26054)
-- Name: mobile_operators; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.mobile_operators (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.mobile_operators OWNER TO masoud;

--
-- TOC entry 205 (class 1259 OID 34600)
-- Name: playlists; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.playlists (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
    name character varying(255) NOT NULL,
    title character varying(255),
    channel uuid NOT NULL,
    created_by uuid,
    deleted_by uuid,
    updated_by uuid,
    created_at timestamp with time zone,
    deleted_at timestamp with time zone,
    updated_at timestamp with time zone,
    details json,
    status integer NOT NULL,
    situation integer NOT NULL,
    description character varying
);


ALTER TABLE public.playlists OWNER TO masoud;

--
-- TOC entry 210 (class 1259 OID 34828)
-- Name: playlists_contents; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.playlists_contents (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.playlists_contents OWNER TO masoud;

--
-- TOC entry 199 (class 1259 OID 26284)
-- Name: privileges; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.privileges (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.privileges OWNER TO masoud;

--
-- TOC entry 190 (class 1259 OID 25546)
-- Name: product_documents_id_seq; Type: SEQUENCE; Schema: public; Owner: angru
--

CREATE SEQUENCE public.product_documents_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.product_documents_id_seq OWNER TO angru;

--
-- TOC entry 191 (class 1259 OID 25548)
-- Name: product_documents; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.product_documents (
    id integer DEFAULT nextval('public.product_documents_id_seq'::regclass) NOT NULL,
    product_id integer,
    name character varying(255),
    title character varying(255),
    path character varying(255),
    size numeric,
    created_at timestamp with time zone,
    deleted_at timestamp with time zone,
    updated_at timestamp with time zone,
    tags json,
    details json,
    status integer,
    description character varying
);


ALTER TABLE public.product_documents OWNER TO masoud;

--
-- TOC entry 188 (class 1259 OID 25535)
-- Name: products_id_seq; Type: SEQUENCE; Schema: public; Owner: angru
--

CREATE SEQUENCE public.products_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.products_id_seq OWNER TO angru;

--
-- TOC entry 189 (class 1259 OID 25537)
-- Name: products; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.products (
    id integer DEFAULT nextval('public.products_id_seq'::regclass) NOT NULL,
    name character varying(255),
    title character varying(255),
    code character varying(255),
    price numeric,
    created_at timestamp with time zone,
    deleted_at timestamp with time zone,
    updated_at timestamp with time zone,
    expirable boolean,
    taxable boolean,
    tags json,
    details json,
    status integer,
    description character varying
);


ALTER TABLE public.products OWNER TO masoud;

--
-- TOC entry 206 (class 1259 OID 34629)
-- Name: publishers; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.publishers (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.publishers OWNER TO masoud;

--
-- TOC entry 217 (class 1259 OID 35059)
-- Name: rates; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.rates (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.rates OWNER TO masoud;

--
-- TOC entry 196 (class 1259 OID 26198)
-- Name: security_roles; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.security_roles (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.security_roles OWNER TO masoud;

--
-- TOC entry 201 (class 1259 OID 26374)
-- Name: services; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.services (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.services OWNER TO masoud;

--
-- TOC entry 203 (class 1259 OID 26442)
-- Name: subscriptions; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.subscriptions (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.subscriptions OWNER TO masoud;

--
-- TOC entry 211 (class 1259 OID 34862)
-- Name: tags; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.tags (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.tags OWNER TO masoud;

--
-- TOC entry 215 (class 1259 OID 34986)
-- Name: tags_channels; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.tags_channels (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.tags_channels OWNER TO masoud;

--
-- TOC entry 213 (class 1259 OID 34918)
-- Name: tags_contents; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.tags_contents (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.tags_contents OWNER TO masoud;

--
-- TOC entry 214 (class 1259 OID 34952)
-- Name: tags_playlists; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.tags_playlists (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.tags_playlists OWNER TO masoud;

--
-- TOC entry 193 (class 1259 OID 25944)
-- Name: users; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.users (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.users OWNER TO masoud;

--
-- TOC entry 207 (class 1259 OID 34658)
-- Name: users_content_providers; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.users_content_providers (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.users_content_providers OWNER TO masoud;

--
-- TOC entry 208 (class 1259 OID 34692)
-- Name: users_publishers; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.users_publishers (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.users_publishers OWNER TO masoud;

--
-- TOC entry 197 (class 1259 OID 26224)
-- Name: users_security_roles; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.users_security_roles (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.users_security_roles OWNER TO masoud;

--
-- TOC entry 212 (class 1259 OID 34888)
-- Name: videos; Type: TABLE; Schema: public; Owner: masoud
--

CREATE TABLE public.videos (
    id uuid DEFAULT public.uuid_generate_v4() NOT NULL,
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
    description character varying
);


ALTER TABLE public.videos OWNER TO masoud;

--
-- TOC entry 2588 (class 0 OID 26005)
-- Dependencies: 194
-- Data for Name: aggrigators; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.aggrigators (id, name, title, code, phone, email, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
92b51153-60e4-4d53-ac29-48e90af4e96f	Hub	Hooshmand Aval Beheshti			info@hub.com	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-20 15:12:21.886611+03:30	\N	\N	{"manager":"sohanian","CTO":"abbasi"}	1	0	
4754f750-6004-4723-823c-a8d607c6b3a4	Tele Promo	Telepromo	0001	+9821883522485	info@telepromo.lb	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-13 21:32:23.551584+03:30	\N	2019-02-20 15:12:43.833562+03:30	{}	1	0	Tele Promo Kish
d10237fd-f43a-4c83-999f-66e13bf6b716	mobin one	m-one	0002	096628816579	info@m-one.com	9979027d-1672-4108-95a4-eb5d346545a0	\N	a2e60f5a-1df2-480d-a034-8d096a9aa83c	2019-02-14 20:43:17.660472+03:30	\N	2019-02-15 22:09:08.816455+03:30	{}	1	0	ENhvIVThfIVKhfXbQaquYEtwiftHNsxRGGoqbHXi
\.


--
-- TOC entry 2612 (class 0 OID 35093)
-- Dependencies: 218
-- Data for Name: attractions; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.attractions (id, member, content, attraction, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2598 (class 0 OID 34566)
-- Dependencies: 204
-- Data for Name: channels; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.channels (id, name, title, service, parent, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
7d7140b5-bba5-4a75-8e9b-6a02e27f0aa6	pink panter		1d345890-5cd7-4026-ab19-53caf5f639a8	\N	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-22 01:27:42.613254+03:30	\N	\N	{}	1	0	
c6c31b48-3158-48f2-b281-f08391bb47ff	season one		1d345890-5cd7-4026-ab19-53caf5f639a8	7d7140b5-bba5-4a75-8e9b-6a02e27f0aa6	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-22 01:28:00.202608+03:30	\N	2019-02-22 01:39:31.232795+03:30	{}	1	0	edit by masoud
7a2473fa-ed26-448e-a212-f3ff2dffdb6e	Tommy		1d345890-5cd7-4026-ab19-53caf5f639a8	\N	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-23 11:09:54.975808+03:30	\N	\N	{}	1	0	
ff6d3411-0f27-4fe6-bd84-33d00e6e6693	Tommy 01		1d345890-5cd7-4026-ab19-53caf5f639a8	7a2473fa-ed26-448e-a212-f3ff2dffdb6e	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-23 11:10:10.452443+03:30	\N	\N	{}	1	0	
\.


--
-- TOC entry 2610 (class 0 OID 35020)
-- Dependencies: 216
-- Data for Name: comments; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.comments (id, member, content, comment, reply_to, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2594 (class 0 OID 26342)
-- Dependencies: 200
-- Data for Name: content_providers; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.content_providers (id, admin, name, title, code, phone, email, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
093ee29b-3491-45e3-9fc4-00eef3ec53bd	65ce394f-d538-4617-8f1f-46dd1dbc8983	mehr	mehr aval	001	+98213342651	info@mehr.io	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-19 22:37:59.985908+03:30	\N	\N	{"manager":"ahmadi"}	1	0	
befc4bde-12ed-4db9-b0f9-c0e14eb14585	a2e60f5a-1df2-480d-a034-8d096a9aa83c	atitel	atitel		+982188753556	info@atitel.net	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-20 15:15:23.444043+03:30	\N	\N	{"account":"milad ahmadi","cto":"alireza"}	1	0	
\.


--
-- TOC entry 2624 (class 0 OID 0)
-- Dependencies: 192
-- Name: content_providers_id_seq; Type: SEQUENCE SET; Schema: public; Owner: angru
--

SELECT pg_catalog.setval('public.content_providers_id_seq', 1, false);


--
-- TOC entry 2603 (class 0 OID 34760)
-- Dependencies: 209
-- Data for Name: contents; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.contents (id, service, publisher, type, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2592 (class 0 OID 26258)
-- Dependencies: 198
-- Data for Name: entities; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.entities (id, name, title, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, type, status, situation, description) FROM stdin;
cdf07567-f987-437b-9087-98bdf89fed1a	entities	entities	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-16 00:09:58.116889+03:30	\N	\N	0	1	0	
8ab2079c-5af9-4d12-9d84-a664e59dc2d5	mobile_operators	mobile_operators	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-16 00:09:58.116889+03:30	\N	\N	0	1	0	
cbf4122c-baf4-4e44-9d85-7e55a3f7d91c	security_roles	security_roles	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-16 00:09:58.116889+03:30	\N	\N	0	1	0	
e534692f-870e-4325-819d-09e3ccb1f116	users	users	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-16 00:09:58.116889+03:30	\N	\N	0	1	0	
98b0fac1-e3bc-4220-9447-22fba5a12b58	users_security_roles	users_security_roles	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-16 00:09:58.116889+03:30	\N	\N	0	1	0	
350a81ec-4da3-4568-a15b-b8e581f8f6ff	privileges	privileges table	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-16 00:09:58.116889+03:30	\N	2019-02-17 02:34:33.072965+03:30	0	1	0	
29c835d5-3049-46de-8aaf-e9f3730aa820	content_providers	content_providers	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-18 00:31:06.348469+03:30	\N	\N	0	1	0	
cb3d5588-c187-4f14-a6da-0214f7ad0540	aggrigators	aggrigators	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-16 00:09:58.116889+03:30	\N	2019-02-20 01:17:53.922678+03:30	0	1	0	
deb07aa8-a2b6-41d2-967a-5aa7960ae4e2	services	services	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-21 18:36:47.280616+03:30	\N	\N	0	1	0	
87b6f47e-5830-4d66-b65a-a80c7fdc7e85	members	members	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-21 18:37:16.616796+03:30	\N	\N	0	1	0	
c46e345b-0810-47be-9c57-1b798829351e	subscriptions	subscriptions	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-21 18:37:38.653679+03:30	\N	\N	0	1	0	
bbc5ed80-3d8b-4ca2-b5bc-35c19a8207af	channels	channels	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-21 18:38:41.838941+03:30	\N	\N	0	1	0	
8e4c6684-27d0-4a3f-9762-feb36db7643f	playlists	playlists	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-21 18:38:57.772756+03:30	\N	\N	0	1	0	
d625b9ed-538b-4717-b2cc-1b186613786f	publishers	publishers	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-21 18:47:09.80543+03:30	\N	\N	0	1	0	
\.


--
-- TOC entry 2596 (class 0 OID 26418)
-- Dependencies: 202
-- Data for Name: members; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.members (id, phone, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
bc04915e-4d73-4aa4-877d-47be2c874431	09124057299	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-20 19:27:45.369938+03:30	\N	2019-02-20 19:30:37.076937+03:30	{"name":"masoud"}	1	0	
24116c59-b621-4d15-9a59-78ccc0f1f04b	09124332516	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-20 19:30:48.819628+03:30	\N	\N	{}	1	0	
\.


--
-- TOC entry 2589 (class 0 OID 26054)
-- Dependencies: 195
-- Data for Name: mobile_operators; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.mobile_operators (id, name, title, code, phone, email, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
60265d78-4be2-41f9-bdc4-028696f69feb	Rightel	Rightel	003	09202000000	info@rightel.ir	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-20 15:09:28.49507+03:30	\N	2019-02-20 15:47:53.037995+03:30	{}	1	0	
0a66159c-6a54-45db-a657-b0fa4945afc3	Hamrah Aval	MCI	0001	1818	info@mci.ir	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-14 18:24:48.720582+03:30	\N	2019-02-20 14:38:26.221613+03:30	{}	1	0	Mobile Telecommunication Company of Iran, commonly abbreviated as MCI and also known under its brand name Hamrahe Aval, is the first and largest mobile operator in Iran. MCI is a subsidiary of the Telecommunication Company of Iran and has approximately 17 million postpaid and 49 million prepaid subscribers.
a8c7638f-9d9e-491f-b5ff-85731a32fc44	Irancell	MTN	0002	0935	info@mtn-irancell.ir	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-14 18:28:03.143696+03:30	\N	2019-02-20 15:46:29.928165+03:30	{"manager":"dezfooli"}	1	0	MTN Irancell
\.


--
-- TOC entry 2599 (class 0 OID 34600)
-- Dependencies: 205
-- Data for Name: playlists; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.playlists (id, name, title, channel, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
c76104f7-36b9-4e0b-8dcb-f5b745b5d763	happy		c6c31b48-3158-48f2-b281-f08391bb47ff	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-22 02:06:35.782792+03:30	\N	\N	{}	1	0	
\.


--
-- TOC entry 2604 (class 0 OID 34828)
-- Dependencies: 210
-- Data for Name: playlists_contents; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.playlists_contents (id, playlist, content, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2593 (class 0 OID 26284)
-- Dependencies: 199
-- Data for Name: privileges; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.privileges (id, security_role, entity, privilege_string, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
24d8fff8-3113-4adc-859b-b6a76032caea	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	e534692f-870e-4325-819d-09e3ccb1f116	11111000000000000000	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-17 20:41:02.693419+03:30	\N	\N	1	0	
4a2a5343-2448-49f7-a2d8-13c57ab39cbf	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	cbf4122c-baf4-4e44-9d85-7e55a3f7d91c	11111000000000000000	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-17 20:41:36.7189+03:30	\N	\N	1	0	
2980d55b-4b56-4731-956f-9d2d16761d74	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	98b0fac1-e3bc-4220-9447-22fba5a12b58	11111000000000000000	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-17 20:41:56.229949+03:30	\N	\N	1	0	
2588e377-6009-4fdb-9fe3-e704bd58c921	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	cdf07567-f987-437b-9087-98bdf89fed1a	11111000000000000000	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-17 20:42:20.123938+03:30	\N	\N	1	0	
9bd87358-97f8-4f92-93e5-5c1569c016fd	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	350a81ec-4da3-4568-a15b-b8e581f8f6ff	11111000000000000000	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-17 20:42:35.801061+03:30	\N	\N	1	0	
e075da20-86f6-4d69-b314-6b236d7759c5	39968d78-6e29-47d5-a8ef-923c9e5724d2	cb3d5588-c187-4f14-a6da-0214f7ad0540	11000000000000000000	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	\N	2019-02-17 22:46:45.818911+03:30	\N	\N	1	0	
3bc6ea57-b3f4-4d51-83d5-af36a0defa57	39968d78-6e29-47d5-a8ef-923c9e5724d2	8ab2079c-5af9-4d12-9d84-a664e59dc2d5	11000000000000000000	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	a2e60f5a-1df2-480d-a034-8d096a9aa83c	2019-02-17 22:46:02.447261+03:30	\N	2019-02-17 22:46:56.255962+03:30	1	0	
2c5d91ea-6e11-441b-8db3-8e3ffe6a17f4	39968d78-6e29-47d5-a8ef-923c9e5724d2	29c835d5-3049-46de-8aaf-e9f3730aa820	11000000000000000000	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	\N	2019-02-18 00:32:16.830891+03:30	\N	\N	1	0	
\.


--
-- TOC entry 2585 (class 0 OID 25548)
-- Dependencies: 191
-- Data for Name: product_documents; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.product_documents (id, product_id, name, title, path, size, created_at, deleted_at, updated_at, tags, details, status, description) FROM stdin;
33	4	0d026d9a-bb5f-51c6-9578-2caac6713be4.jpg		/home/masoud/Projects/angru/files/15498507188890d026d9a-bb5f-51c6-9578-2caac6713be4.jpg	46381	2019-02-11 05:35:18.950707+03:30	\N	\N	[]	{}	1	
31	1	اجرای کاور قطعهیطلوع من سیاوش قمیشی توسط محسن نامجو.mp3		/home/masoud/Projects/angru/files/1549843509316اجرای کاور قطعهیطلوع من سیاوش قمیشی توسط محسن نامجو.mp3	10067519	2019-02-11 03:35:09.377469+03:30	\N	\N	[]	{}	1	
32	1	LICENSE		/home/masoud/Projects/angru/files/1549843529678LICENSE	1097	2019-02-11 03:35:29.71767+03:30	\N	\N	[]	{}	1	
\.


--
-- TOC entry 2625 (class 0 OID 0)
-- Dependencies: 190
-- Name: product_documents_id_seq; Type: SEQUENCE SET; Schema: public; Owner: angru
--

SELECT pg_catalog.setval('public.product_documents_id_seq', 33, true);


--
-- TOC entry 2583 (class 0 OID 25537)
-- Dependencies: 189
-- Data for Name: products; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.products (id, name, title, code, price, created_at, deleted_at, updated_at, expirable, taxable, tags, details, status, description) FROM stdin;
2	sculpture	keyboard	123k	45.299999	2019-02-06 17:16:29.620132+03:30	2019-02-06 18:37:20.298463+03:30	\N	t	t	[]	{}	1	
3	pen	bik pen	3459g	1.76	2019-02-06 18:34:59.915057+03:30	2019-02-06 18:37:20.301152+03:30	2019-02-06 18:36:51.913216+03:30	t	f	["pen","Bik"]	{"color":"red"}	0	pen bik hero!
1	lg3240	lg 3240	l3240g	128.39999	2019-02-06 13:27:36.05643+03:30	\N	2019-02-07 18:43:50.318082+03:30	t	f	["lg","smartphone","sdfasdf","yuiuyi","tyutye"]	{"factory":"lg"}	0	
4	watch ceiko5	ceiko5	c34tw-b	693.98999	2019-02-06 18:43:20.460254+03:30	\N	2019-02-19 12:14:59.841634+03:30	f	t	["saat"]	{"size":"large","name":"kala"}	1	watch me!
\.


--
-- TOC entry 2626 (class 0 OID 0)
-- Dependencies: 188
-- Name: products_id_seq; Type: SEQUENCE SET; Schema: public; Owner: angru
--

SELECT pg_catalog.setval('public.products_id_seq', 4, true);


--
-- TOC entry 2600 (class 0 OID 34629)
-- Dependencies: 206
-- Data for Name: publishers; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.publishers (id, admin, name, title, code, phone, email, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
5b9e81ce-556c-4324-890f-2cb6fd188038	a2e60f5a-1df2-480d-a034-8d096a9aa83c	sedaye iran novin	iran seda	001	+98218834252	info@seda.ir	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-21 23:26:11.144512+03:30	\N	2019-02-21 23:26:32.181936+03:30	{"manager":"irani"}	1	0	
\.


--
-- TOC entry 2611 (class 0 OID 35059)
-- Dependencies: 217
-- Data for Name: rates; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.rates (id, member, content, rate, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2590 (class 0 OID 26198)
-- Dependencies: 196
-- Data for Name: security_roles; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.security_roles (id, name, title, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
3d2964c4-47b5-40ce-bf55-ec68e7ec16e2	reporter	create and run report	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-16 01:54:46.690384+03:30	\N	2019-02-17 20:31:47.742775+03:30	1	0	
39968d78-6e29-47d5-a8ef-923c9e5724d2	service manager	service manager	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-16 19:29:42.235301+03:30	\N	2019-02-20 01:04:31.674183+03:30	1	0	service manager for managing service
3c230a5e-76a9-48a6-a51b-60fb3a8f7117	security manager	management of security and privileges	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-17 20:30:13.869463+03:30	\N	2019-02-20 01:06:04.677152+03:30	1	0	security
b5a2e7ab-d9fa-4db9-9f45-6a53b0094d7d	content manager	content manager	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-16 01:54:26.707996+03:30	\N	2019-02-20 15:17:28.319967+03:30	1	0	
\.


--
-- TOC entry 2595 (class 0 OID 26374)
-- Dependencies: 201
-- Data for Name: services; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.services (id, pendar, mobile_operator, aggrigator, content_provider, name, title, code, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
1d345890-5cd7-4026-ab19-53caf5f639a8	fd2255b0-9ce3-4372-89dc-e3945ce2c16d	0a66159c-6a54-45db-a657-b0fa4945afc3	4754f750-6004-4723-823c-a8d607c6b3a4	befc4bde-12ed-4db9-b0f9-c0e14eb14585	cartoon3	cartoon3		9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-20 15:10:28.87766+03:30	\N	2019-02-20 15:37:52.268429+03:30	{}	1	0	
\.


--
-- TOC entry 2597 (class 0 OID 26442)
-- Dependencies: 203
-- Data for Name: subscriptions; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.subscriptions (id, member, service, last_login, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
3ff456f7-75f7-42aa-8d94-0890d5e38213	bc04915e-4d73-4aa4-877d-47be2c874431	1d345890-5cd7-4026-ab19-53caf5f639a8	2019-02-20 00:00:00+03:30	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-20 20:05:11.811352+03:30	\N	\N	{}	1	0	
\.


--
-- TOC entry 2605 (class 0 OID 34862)
-- Dependencies: 211
-- Data for Name: tags; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.tags (id, name, title, type, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2609 (class 0 OID 34986)
-- Dependencies: 215
-- Data for Name: tags_channels; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.tags_channels (id, tag, channel, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2607 (class 0 OID 34918)
-- Dependencies: 213
-- Data for Name: tags_contents; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.tags_contents (id, tag, content, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2608 (class 0 OID 34952)
-- Dependencies: 214
-- Data for Name: tags_playlists; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.tags_playlists (id, tag, playlist, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2587 (class 0 OID 25944)
-- Dependencies: 193
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.users (id, first_name, middle_name, last_name, username, email, password, type, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
9979027d-1672-4108-95a4-eb5d346545a0	zeus	G	god	zeus	zeus@olympus.god	7c4a8d09ca3762af61e59520943dc26494f8941b	0	\N	\N	\N	2019-02-13 15:13:44.238385+03:30	\N	\N	{}	1	1	Zeus is the sky and thunder god in ancient Greek religion, who rules as king of the gods of Mount Olympus. His name is cognate with the first element of his Roman equivalent Jupiter. His mythologies and powers are similar, though not identical, to those of Indo-European deities such as Indra, Jupiter, Perkūnas, Perun, and Thor
65ce394f-d538-4617-8f1f-46dd1dbc8983	hasan	m	mirahadi	hasan	hasan@atitel.com	7110eda4d09e062aa5e4a390b0a572ac0d2c0220	2	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-16 02:01:11.024943+03:30	\N	2019-02-20 00:58:19.26597+03:30	{"position":"manager","weight":"78"}	1	1	
a2e60f5a-1df2-480d-a034-8d096a9aa83c	masoud	b	bolhassani	masoud	masoud@atitel.com	7110eda4d09e062aa5e4a390b0a572ac0d2c0220	2	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-13 15:17:46.679052+03:30	\N	2019-02-20 01:05:20.678576+03:30	{}	1	1	
\.


--
-- TOC entry 2601 (class 0 OID 34658)
-- Dependencies: 207
-- Data for Name: users_content_providers; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.users_content_providers (id, _user_, content_provider, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
3d08a387-d319-4059-83cf-a8c2075e71f8	65ce394f-d538-4617-8f1f-46dd1dbc8983	befc4bde-12ed-4db9-b0f9-c0e14eb14585	9979027d-1672-4108-95a4-eb5d346545a0	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-23 12:42:14.610806+03:30	\N	2019-02-23 13:44:38.65722+03:30	1	0	
\.


--
-- TOC entry 2602 (class 0 OID 34692)
-- Dependencies: 208
-- Data for Name: users_publishers; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.users_publishers (id, _user_, publisher, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
91832ee9-a57e-47c6-b508-777e323680f2	a2e60f5a-1df2-480d-a034-8d096a9aa83c	5b9e81ce-556c-4324-890f-2cb6fd188038	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-23 14:32:09.096168+03:30	\N	\N	1	0	
\.


--
-- TOC entry 2591 (class 0 OID 26224)
-- Dependencies: 197
-- Data for Name: users_security_roles; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.users_security_roles (id, _user_, security_role, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, status, situation, description) FROM stdin;
e17ef899-7a44-4164-b8b9-d74f1afc1463	a2e60f5a-1df2-480d-a034-8d096a9aa83c	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-17 20:39:49.303664+03:30	\N	\N	1	0	
1a7840a2-1b9e-4c19-8561-583a81e314c5	65ce394f-d538-4617-8f1f-46dd1dbc8983	3c230a5e-76a9-48a6-a51b-60fb3a8f7117	9979027d-1672-4108-95a4-eb5d346545a0	\N	\N	2019-02-18 14:43:13.463646+03:30	\N	\N	1	0	
25d78a9c-949e-443e-905d-7ceaf3e705bd	65ce394f-d538-4617-8f1f-46dd1dbc8983	39968d78-6e29-47d5-a8ef-923c9e5724d2	a2e60f5a-1df2-480d-a034-8d096a9aa83c	\N	9979027d-1672-4108-95a4-eb5d346545a0	2019-02-17 22:45:39.047082+03:30	\N	2019-02-20 01:09:43.190841+03:30	1	0	hasan is service manager
\.


--
-- TOC entry 2606 (class 0 OID 34888)
-- Dependencies: 212
-- Data for Name: videos; Type: TABLE DATA; Schema: public; Owner: masoud
--

COPY public.videos (id, content, name, title, path, size, created_by, deleted_by, updated_by, created_at, deleted_at, updated_at, details, status, situation, description) FROM stdin;
\.


--
-- TOC entry 2293 (class 2606 OID 26013)
-- Name: aggrigators aggrigators_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.aggrigators
    ADD CONSTRAINT aggrigators_pkey PRIMARY KEY (id);


--
-- TOC entry 2349 (class 2606 OID 35101)
-- Name: attractions attractions_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.attractions
    ADD CONSTRAINT attractions_pkey PRIMARY KEY (id);


--
-- TOC entry 2319 (class 2606 OID 34574)
-- Name: channels channels_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_pkey PRIMARY KEY (id);


--
-- TOC entry 2345 (class 2606 OID 35028)
-- Name: comments comments_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_pkey PRIMARY KEY (id);


--
-- TOC entry 2309 (class 2606 OID 26350)
-- Name: content_providers content_providers_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.content_providers
    ADD CONSTRAINT content_providers_pkey PRIMARY KEY (id);


--
-- TOC entry 2329 (class 2606 OID 34768)
-- Name: contents contents_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.contents
    ADD CONSTRAINT contents_pkey PRIMARY KEY (id);


--
-- TOC entry 2303 (class 2606 OID 26266)
-- Name: entities entities_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.entities
    ADD CONSTRAINT entities_pkey PRIMARY KEY (id);


--
-- TOC entry 2305 (class 2606 OID 26268)
-- Name: entities entities_ukey_name; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.entities
    ADD CONSTRAINT entities_ukey_name UNIQUE (name);


--
-- TOC entry 2315 (class 2606 OID 26426)
-- Name: members members_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.members
    ADD CONSTRAINT members_pkey PRIMARY KEY (id);


--
-- TOC entry 2295 (class 2606 OID 26062)
-- Name: mobile_operators mobile_operators_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.mobile_operators
    ADD CONSTRAINT mobile_operators_pkey PRIMARY KEY (id);


--
-- TOC entry 2331 (class 2606 OID 34836)
-- Name: playlists_contents playlists_contents_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists_contents
    ADD CONSTRAINT playlists_contents_pkey PRIMARY KEY (id);


--
-- TOC entry 2321 (class 2606 OID 34608)
-- Name: playlists playlists_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists
    ADD CONSTRAINT playlists_pkey PRIMARY KEY (id);


--
-- TOC entry 2307 (class 2606 OID 26292)
-- Name: privileges privileges_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.privileges
    ADD CONSTRAINT privileges_pkey PRIMARY KEY (id);


--
-- TOC entry 2285 (class 2606 OID 25556)
-- Name: product_documents product_documents_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.product_documents
    ADD CONSTRAINT product_documents_pkey PRIMARY KEY (id);


--
-- TOC entry 2283 (class 2606 OID 25545)
-- Name: products products_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_pkey PRIMARY KEY (id);


--
-- TOC entry 2323 (class 2606 OID 34637)
-- Name: publishers publishers_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.publishers
    ADD CONSTRAINT publishers_pkey PRIMARY KEY (id);


--
-- TOC entry 2347 (class 2606 OID 35067)
-- Name: rates rates_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.rates
    ADD CONSTRAINT rates_pkey PRIMARY KEY (id);


--
-- TOC entry 2297 (class 2606 OID 26206)
-- Name: security_roles security_roles_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.security_roles
    ADD CONSTRAINT security_roles_pkey PRIMARY KEY (id);


--
-- TOC entry 2299 (class 2606 OID 26208)
-- Name: security_roles security_roles_ukey_name; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.security_roles
    ADD CONSTRAINT security_roles_ukey_name UNIQUE (name);


--
-- TOC entry 2311 (class 2606 OID 26382)
-- Name: services services_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_pkey PRIMARY KEY (id);


--
-- TOC entry 2313 (class 2606 OID 26384)
-- Name: services services_ukey_pendar; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_ukey_pendar UNIQUE (pendar);


--
-- TOC entry 2317 (class 2606 OID 26450)
-- Name: subscriptions subscriptions_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.subscriptions
    ADD CONSTRAINT subscriptions_pkey PRIMARY KEY (id);


--
-- TOC entry 2343 (class 2606 OID 34994)
-- Name: tags_channels tags_channels_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_channels
    ADD CONSTRAINT tags_channels_pkey PRIMARY KEY (id);


--
-- TOC entry 2339 (class 2606 OID 34926)
-- Name: tags_contents tags_contents_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_contents
    ADD CONSTRAINT tags_contents_pkey PRIMARY KEY (id);


--
-- TOC entry 2333 (class 2606 OID 34870)
-- Name: tags tags_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags
    ADD CONSTRAINT tags_pkey PRIMARY KEY (id);


--
-- TOC entry 2341 (class 2606 OID 34960)
-- Name: tags_playlists tags_playlists_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_playlists
    ADD CONSTRAINT tags_playlists_pkey PRIMARY KEY (id);


--
-- TOC entry 2335 (class 2606 OID 34872)
-- Name: tags tags_ukey_name; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags
    ADD CONSTRAINT tags_ukey_name UNIQUE (name);


--
-- TOC entry 2325 (class 2606 OID 34666)
-- Name: users_content_providers users_content_providers_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_content_providers
    ADD CONSTRAINT users_content_providers_pkey PRIMARY KEY (id);


--
-- TOC entry 2287 (class 2606 OID 25952)
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- TOC entry 2327 (class 2606 OID 34700)
-- Name: users_publishers users_publishers_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_publishers
    ADD CONSTRAINT users_publishers_pkey PRIMARY KEY (id);


--
-- TOC entry 2301 (class 2606 OID 26232)
-- Name: users_security_roles users_security_roles_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_security_roles
    ADD CONSTRAINT users_security_roles_pkey PRIMARY KEY (id);


--
-- TOC entry 2289 (class 2606 OID 25954)
-- Name: users users_ukey_email; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_ukey_email UNIQUE (email);


--
-- TOC entry 2291 (class 2606 OID 25956)
-- Name: users users_ukey_username; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_ukey_username UNIQUE (username);


--
-- TOC entry 2337 (class 2606 OID 34896)
-- Name: videos videos_pkey; Type: CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_pkey PRIMARY KEY (id);


--
-- TOC entry 2460 (class 2606 OID 35102)
-- Name: attractions attractions_content_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.attractions
    ADD CONSTRAINT attractions_content_fkey FOREIGN KEY (content) REFERENCES public.contents(id);


--
-- TOC entry 2461 (class 2606 OID 35107)
-- Name: attractions attractions_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.attractions
    ADD CONSTRAINT attractions_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2462 (class 2606 OID 35112)
-- Name: attractions attractions_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.attractions
    ADD CONSTRAINT attractions_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2463 (class 2606 OID 35117)
-- Name: attractions attractions_member_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.attractions
    ADD CONSTRAINT attractions_member_fkey FOREIGN KEY (member) REFERENCES public.members(id);


--
-- TOC entry 2464 (class 2606 OID 35122)
-- Name: attractions attractions_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.attractions
    ADD CONSTRAINT attractions_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2396 (class 2606 OID 34585)
-- Name: channels channels_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2397 (class 2606 OID 34590)
-- Name: channels channels_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2395 (class 2606 OID 34580)
-- Name: channels channels_parent_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_parent_fkey FOREIGN KEY (parent) REFERENCES public.channels(id);


--
-- TOC entry 2394 (class 2606 OID 34575)
-- Name: channels channels_service_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_service_fkey FOREIGN KEY (service) REFERENCES public.services(id);


--
-- TOC entry 2398 (class 2606 OID 34595)
-- Name: channels channels_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.channels
    ADD CONSTRAINT channels_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2452 (class 2606 OID 35044)
-- Name: comments comments_content_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_content_fkey FOREIGN KEY (content) REFERENCES public.contents(id);


--
-- TOC entry 2450 (class 2606 OID 35034)
-- Name: comments comments_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2451 (class 2606 OID 35039)
-- Name: comments comments_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2449 (class 2606 OID 35029)
-- Name: comments comments_member_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_member_fkey FOREIGN KEY (member) REFERENCES public.members(id);


--
-- TOC entry 2454 (class 2606 OID 35054)
-- Name: comments comments_reply_to_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_reply_to_fkey FOREIGN KEY (reply_to) REFERENCES public.comments(id);


--
-- TOC entry 2453 (class 2606 OID 35049)
-- Name: comments comments_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.comments
    ADD CONSTRAINT comments_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2376 (class 2606 OID 26351)
-- Name: content_providers content_providers_admin_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.content_providers
    ADD CONSTRAINT content_providers_admin_fkey FOREIGN KEY (admin) REFERENCES public.users(id);


--
-- TOC entry 2377 (class 2606 OID 26356)
-- Name: content_providers content_providers_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.content_providers
    ADD CONSTRAINT content_providers_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2378 (class 2606 OID 26361)
-- Name: content_providers content_providers_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.content_providers
    ADD CONSTRAINT content_providers_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2379 (class 2606 OID 26366)
-- Name: content_providers content_providers_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.content_providers
    ADD CONSTRAINT content_providers_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2419 (class 2606 OID 34779)
-- Name: contents contents_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.contents
    ADD CONSTRAINT contents_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2420 (class 2606 OID 34784)
-- Name: contents contents_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.contents
    ADD CONSTRAINT contents_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2418 (class 2606 OID 34774)
-- Name: contents contents_publisher_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.contents
    ADD CONSTRAINT contents_publisher_fkey FOREIGN KEY (publisher) REFERENCES public.publishers(id);


--
-- TOC entry 2417 (class 2606 OID 34769)
-- Name: contents contents_service_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.contents
    ADD CONSTRAINT contents_service_fkey FOREIGN KEY (service) REFERENCES public.services(id);


--
-- TOC entry 2421 (class 2606 OID 34789)
-- Name: contents contents_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.contents
    ADD CONSTRAINT contents_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2368 (class 2606 OID 26269)
-- Name: entities entities_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.entities
    ADD CONSTRAINT entities_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2369 (class 2606 OID 26274)
-- Name: entities entities_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.entities
    ADD CONSTRAINT entities_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2370 (class 2606 OID 26279)
-- Name: entities entities_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.entities
    ADD CONSTRAINT entities_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2386 (class 2606 OID 26427)
-- Name: members members_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.members
    ADD CONSTRAINT members_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2387 (class 2606 OID 26432)
-- Name: members members_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.members
    ADD CONSTRAINT members_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2388 (class 2606 OID 26437)
-- Name: members members_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.members
    ADD CONSTRAINT members_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2357 (class 2606 OID 26063)
-- Name: mobile_operators mobile_operators_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.mobile_operators
    ADD CONSTRAINT mobile_operators_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2358 (class 2606 OID 26068)
-- Name: mobile_operators mobile_operators_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.mobile_operators
    ADD CONSTRAINT mobile_operators_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2359 (class 2606 OID 26073)
-- Name: mobile_operators mobile_operators_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.mobile_operators
    ADD CONSTRAINT mobile_operators_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2399 (class 2606 OID 34609)
-- Name: playlists playlists_channel_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists
    ADD CONSTRAINT playlists_channel_fkey FOREIGN KEY (channel) REFERENCES public.channels(id);


--
-- TOC entry 2425 (class 2606 OID 34852)
-- Name: playlists_contents playlists_contents_content_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists_contents
    ADD CONSTRAINT playlists_contents_content_fkey FOREIGN KEY (content) REFERENCES public.contents(id);


--
-- TOC entry 2423 (class 2606 OID 34842)
-- Name: playlists_contents playlists_contents_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists_contents
    ADD CONSTRAINT playlists_contents_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2424 (class 2606 OID 34847)
-- Name: playlists_contents playlists_contents_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists_contents
    ADD CONSTRAINT playlists_contents_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2422 (class 2606 OID 34837)
-- Name: playlists_contents playlists_contents_playlist_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists_contents
    ADD CONSTRAINT playlists_contents_playlist_fkey FOREIGN KEY (playlist) REFERENCES public.playlists(id);


--
-- TOC entry 2426 (class 2606 OID 34857)
-- Name: playlists_contents playlists_contents_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists_contents
    ADD CONSTRAINT playlists_contents_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2400 (class 2606 OID 34614)
-- Name: playlists playlists_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists
    ADD CONSTRAINT playlists_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2401 (class 2606 OID 34619)
-- Name: playlists playlists_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists
    ADD CONSTRAINT playlists_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2402 (class 2606 OID 34624)
-- Name: playlists playlists_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.playlists
    ADD CONSTRAINT playlists_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2373 (class 2606 OID 26303)
-- Name: privileges privileges_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.privileges
    ADD CONSTRAINT privileges_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2374 (class 2606 OID 26308)
-- Name: privileges privileges_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.privileges
    ADD CONSTRAINT privileges_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2372 (class 2606 OID 26298)
-- Name: privileges privileges_entity_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.privileges
    ADD CONSTRAINT privileges_entity_fkey FOREIGN KEY (entity) REFERENCES public.entities(id);


--
-- TOC entry 2371 (class 2606 OID 26293)
-- Name: privileges privileges_security_role_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.privileges
    ADD CONSTRAINT privileges_security_role_fkey FOREIGN KEY (security_role) REFERENCES public.security_roles(id);


--
-- TOC entry 2375 (class 2606 OID 26313)
-- Name: privileges privileges_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.privileges
    ADD CONSTRAINT privileges_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2350 (class 2606 OID 25557)
-- Name: product_documents product_documents_product_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.product_documents
    ADD CONSTRAINT product_documents_product_id_fkey FOREIGN KEY (product_id) REFERENCES public.products(id);


--
-- TOC entry 2403 (class 2606 OID 34638)
-- Name: publishers publishers_admin_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.publishers
    ADD CONSTRAINT publishers_admin_fkey FOREIGN KEY (admin) REFERENCES public.users(id);


--
-- TOC entry 2404 (class 2606 OID 34643)
-- Name: publishers publishers_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.publishers
    ADD CONSTRAINT publishers_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2405 (class 2606 OID 34648)
-- Name: publishers publishers_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.publishers
    ADD CONSTRAINT publishers_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2406 (class 2606 OID 34653)
-- Name: publishers publishers_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.publishers
    ADD CONSTRAINT publishers_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2455 (class 2606 OID 35068)
-- Name: rates rates_content_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.rates
    ADD CONSTRAINT rates_content_fkey FOREIGN KEY (content) REFERENCES public.contents(id);


--
-- TOC entry 2456 (class 2606 OID 35073)
-- Name: rates rates_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.rates
    ADD CONSTRAINT rates_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2457 (class 2606 OID 35078)
-- Name: rates rates_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.rates
    ADD CONSTRAINT rates_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2458 (class 2606 OID 35083)
-- Name: rates rates_member_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.rates
    ADD CONSTRAINT rates_member_fkey FOREIGN KEY (member) REFERENCES public.members(id);


--
-- TOC entry 2459 (class 2606 OID 35088)
-- Name: rates rates_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.rates
    ADD CONSTRAINT rates_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2360 (class 2606 OID 26209)
-- Name: security_roles security_roles_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.security_roles
    ADD CONSTRAINT security_roles_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2361 (class 2606 OID 26214)
-- Name: security_roles security_roles_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.security_roles
    ADD CONSTRAINT security_roles_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2362 (class 2606 OID 26219)
-- Name: security_roles security_roles_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.security_roles
    ADD CONSTRAINT security_roles_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2381 (class 2606 OID 26390)
-- Name: services services_aggrigator_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_aggrigator_fkey FOREIGN KEY (aggrigator) REFERENCES public.aggrigators(id);


--
-- TOC entry 2382 (class 2606 OID 26395)
-- Name: services services_content_provider_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_content_provider_fkey FOREIGN KEY (content_provider) REFERENCES public.content_providers(id);


--
-- TOC entry 2383 (class 2606 OID 26400)
-- Name: services services_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2384 (class 2606 OID 26405)
-- Name: services services_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2380 (class 2606 OID 26385)
-- Name: services services_mobile_operator_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_mobile_operator_fkey FOREIGN KEY (mobile_operator) REFERENCES public.mobile_operators(id);


--
-- TOC entry 2385 (class 2606 OID 26410)
-- Name: services services_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2391 (class 2606 OID 26461)
-- Name: subscriptions subscriptions_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.subscriptions
    ADD CONSTRAINT subscriptions_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2392 (class 2606 OID 26466)
-- Name: subscriptions subscriptions_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.subscriptions
    ADD CONSTRAINT subscriptions_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2389 (class 2606 OID 26451)
-- Name: subscriptions subscriptions_member_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.subscriptions
    ADD CONSTRAINT subscriptions_member_fkey FOREIGN KEY (member) REFERENCES public.members(id);


--
-- TOC entry 2390 (class 2606 OID 26456)
-- Name: subscriptions subscriptions_service_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.subscriptions
    ADD CONSTRAINT subscriptions_service_fkey FOREIGN KEY (service) REFERENCES public.services(id);


--
-- TOC entry 2393 (class 2606 OID 26471)
-- Name: subscriptions subscriptions_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.subscriptions
    ADD CONSTRAINT subscriptions_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2447 (class 2606 OID 35010)
-- Name: tags_channels tags_channels_channel_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_channels
    ADD CONSTRAINT tags_channels_channel_fkey FOREIGN KEY (channel) REFERENCES public.channels(id);


--
-- TOC entry 2445 (class 2606 OID 35000)
-- Name: tags_channels tags_channels_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_channels
    ADD CONSTRAINT tags_channels_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2446 (class 2606 OID 35005)
-- Name: tags_channels tags_channels_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_channels
    ADD CONSTRAINT tags_channels_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2444 (class 2606 OID 34995)
-- Name: tags_channels tags_channels_tag_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_channels
    ADD CONSTRAINT tags_channels_tag_fkey FOREIGN KEY (tag) REFERENCES public.tags(id);


--
-- TOC entry 2448 (class 2606 OID 35015)
-- Name: tags_channels tags_channels_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_channels
    ADD CONSTRAINT tags_channels_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2437 (class 2606 OID 34942)
-- Name: tags_contents tags_contents_content_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_contents
    ADD CONSTRAINT tags_contents_content_fkey FOREIGN KEY (content) REFERENCES public.contents(id);


--
-- TOC entry 2435 (class 2606 OID 34932)
-- Name: tags_contents tags_contents_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_contents
    ADD CONSTRAINT tags_contents_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2436 (class 2606 OID 34937)
-- Name: tags_contents tags_contents_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_contents
    ADD CONSTRAINT tags_contents_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2434 (class 2606 OID 34927)
-- Name: tags_contents tags_contents_tag_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_contents
    ADD CONSTRAINT tags_contents_tag_fkey FOREIGN KEY (tag) REFERENCES public.tags(id);


--
-- TOC entry 2438 (class 2606 OID 34947)
-- Name: tags_contents tags_contents_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_contents
    ADD CONSTRAINT tags_contents_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2427 (class 2606 OID 34873)
-- Name: tags tags_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags
    ADD CONSTRAINT tags_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2428 (class 2606 OID 34878)
-- Name: tags tags_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags
    ADD CONSTRAINT tags_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2440 (class 2606 OID 34966)
-- Name: tags_playlists tags_playlists_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_playlists
    ADD CONSTRAINT tags_playlists_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2441 (class 2606 OID 34971)
-- Name: tags_playlists tags_playlists_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_playlists
    ADD CONSTRAINT tags_playlists_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2442 (class 2606 OID 34976)
-- Name: tags_playlists tags_playlists_playlist_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_playlists
    ADD CONSTRAINT tags_playlists_playlist_fkey FOREIGN KEY (playlist) REFERENCES public.playlists(id);


--
-- TOC entry 2439 (class 2606 OID 34961)
-- Name: tags_playlists tags_playlists_tag_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_playlists
    ADD CONSTRAINT tags_playlists_tag_fkey FOREIGN KEY (tag) REFERENCES public.tags(id);


--
-- TOC entry 2443 (class 2606 OID 34981)
-- Name: tags_playlists tags_playlists_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags_playlists
    ADD CONSTRAINT tags_playlists_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2429 (class 2606 OID 34883)
-- Name: tags tags_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.tags
    ADD CONSTRAINT tags_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2407 (class 2606 OID 34667)
-- Name: users_content_providers users_content_providers__user__fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_content_providers
    ADD CONSTRAINT users_content_providers__user__fkey FOREIGN KEY (_user_) REFERENCES public.users(id);


--
-- TOC entry 2410 (class 2606 OID 34682)
-- Name: users_content_providers users_content_providers_content_provider_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_content_providers
    ADD CONSTRAINT users_content_providers_content_provider_fkey FOREIGN KEY (content_provider) REFERENCES public.content_providers(id);


--
-- TOC entry 2408 (class 2606 OID 34672)
-- Name: users_content_providers users_content_providers_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_content_providers
    ADD CONSTRAINT users_content_providers_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2409 (class 2606 OID 34677)
-- Name: users_content_providers users_content_providers_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_content_providers
    ADD CONSTRAINT users_content_providers_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2411 (class 2606 OID 34687)
-- Name: users_content_providers users_content_providers_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_content_providers
    ADD CONSTRAINT users_content_providers_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2351 (class 2606 OID 25957)
-- Name: users users_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2354 (class 2606 OID 26014)
-- Name: aggrigators users_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.aggrigators
    ADD CONSTRAINT users_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2352 (class 2606 OID 25962)
-- Name: users users_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2355 (class 2606 OID 26019)
-- Name: aggrigators users_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.aggrigators
    ADD CONSTRAINT users_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2412 (class 2606 OID 34701)
-- Name: users_publishers users_publishers__user__fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_publishers
    ADD CONSTRAINT users_publishers__user__fkey FOREIGN KEY (_user_) REFERENCES public.users(id);


--
-- TOC entry 2413 (class 2606 OID 34706)
-- Name: users_publishers users_publishers_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_publishers
    ADD CONSTRAINT users_publishers_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2414 (class 2606 OID 34711)
-- Name: users_publishers users_publishers_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_publishers
    ADD CONSTRAINT users_publishers_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2415 (class 2606 OID 34716)
-- Name: users_publishers users_publishers_publisher_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_publishers
    ADD CONSTRAINT users_publishers_publisher_fkey FOREIGN KEY (publisher) REFERENCES public.publishers(id);


--
-- TOC entry 2416 (class 2606 OID 34721)
-- Name: users_publishers users_publishers_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_publishers
    ADD CONSTRAINT users_publishers_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2365 (class 2606 OID 26243)
-- Name: users_security_roles users_security_roles__user__fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_security_roles
    ADD CONSTRAINT users_security_roles__user__fkey FOREIGN KEY (_user_) REFERENCES public.users(id);


--
-- TOC entry 2363 (class 2606 OID 26233)
-- Name: users_security_roles users_security_roles_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_security_roles
    ADD CONSTRAINT users_security_roles_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2364 (class 2606 OID 26238)
-- Name: users_security_roles users_security_roles_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_security_roles
    ADD CONSTRAINT users_security_roles_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2366 (class 2606 OID 26248)
-- Name: users_security_roles users_security_roles_security_role_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_security_roles
    ADD CONSTRAINT users_security_roles_security_role_fkey FOREIGN KEY (security_role) REFERENCES public.security_roles(id);


--
-- TOC entry 2367 (class 2606 OID 26253)
-- Name: users_security_roles users_security_roles_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users_security_roles
    ADD CONSTRAINT users_security_roles_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2353 (class 2606 OID 25967)
-- Name: users users_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2356 (class 2606 OID 26024)
-- Name: aggrigators users_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.aggrigators
    ADD CONSTRAINT users_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


--
-- TOC entry 2432 (class 2606 OID 34907)
-- Name: videos videos_content_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_content_fkey FOREIGN KEY (content) REFERENCES public.contents(id);


--
-- TOC entry 2430 (class 2606 OID 34897)
-- Name: videos videos_created_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_created_by_fkey FOREIGN KEY (created_by) REFERENCES public.users(id);


--
-- TOC entry 2431 (class 2606 OID 34902)
-- Name: videos videos_deleted_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_deleted_by_fkey FOREIGN KEY (deleted_by) REFERENCES public.users(id);


--
-- TOC entry 2433 (class 2606 OID 34912)
-- Name: videos videos_updated_by_fkey; Type: FK CONSTRAINT; Schema: public; Owner: masoud
--

ALTER TABLE ONLY public.videos
    ADD CONSTRAINT videos_updated_by_fkey FOREIGN KEY (updated_by) REFERENCES public.users(id);


-- Completed on 2019-02-24 11:48:24 +0330

--
-- PostgreSQL database dump complete
--

