CREATE TABLE public.content_type (
    id uuid NOT NULL,
    name character varying(255) NOT NULL,
    fields jsonb NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone,
    deleted_at timestamp with time zone
);

CREATE TABLE public.cp (
    id uuid NOT NULL,
    name character varying(255) NOT NULL,
    description text,
    phone character varying(12) NOT NULL,
    email character varying(255),
    metadata jsonb,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone,
    deleted_at timestamp with time zone
);


CREATE TABLE public.category (
    id uuid NOT NULL,
    title character varying(128) NOT NULL,
    status public.status DEFAULT 'enable'::public.status NOT NULL,
    files jsonb DEFAULT '{}'::jsonb NOT NULL,
    description text DEFAULT ''::text NOT NULL,
    service_id uuid NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone,
    deleted_at timestamp with time zone,
    metadata jsonb
);

CREATE TABLE public.comment (
    id uuid NOT NULL,
    profile_id uuid NOT NULL,
    status public.status DEFAULT 'pending'::public.status NOT NULL,
    comment text NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone,
    deleted_at timestamp with time zone,
    content_id uuid NOT NULL
);

CREATE TABLE public.content (
    id uuid NOT NULL,
    title character varying(255) NOT NULL,
    subtitle text,
    description text,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone,
    deleted_at timestamp with time zone,
    type character varying(16) DEFAULT 'video'::text NOT NULL,
    status public.status DEFAULT 'new'::public.status NOT NULL,
    files jsonb DEFAULT '{}'::jsonb,
    category_id uuid NOT NULL,
    additionals jsonb DEFAULT '{}'::jsonb NOT NULL,
    price integer DEFAULT 0 NOT NULL,
    content_type_id uuid NOT NULL,
    service_id uuid NOT NULL,
    priority smallint DEFAULT 1 NOT NULL,
    playlist_id uuid NOT NULL,
    original_files jsonb NOT NULL,
    worker_status public.worker_status DEFAULT 'queue'::public.worker_status NOT NULL
);

CREATE TABLE public.jdate (
    gdate date NOT NULL,
    jdate character varying(16) NOT NULL,
    jyear smallint NOT NULL,
    jmonth smallint NOT NULL,
    jday smallint NOT NULL,
    jdayname character varying(64) NOT NULL,
    jmonthname character varying(64) NOT NULL
);

CREATE TABLE public."like" (
    id uuid NOT NULL,
    profile_id uuid NOT NULL,
    content_id uuid NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone
);

CREATE TABLE public.playlist (
    id uuid NOT NULL,
    service_id uuid NOT NULL,
    category_id uuid NOT NULL,
    title character varying(255) NOT NULL,
    description text,
    files jsonb,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone,
    metadata jsonb
);

CREATE TABLE public.profile (
    id uuid NOT NULL,
    username character varying(32) NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone,
    status public.status DEFAULT 'new'::public.status NOT NULL,
    metadata jsonb DEFAULT '{}'::jsonb NOT NULL,
    service_id uuid NOT NULL
);

CREATE TABLE public.service (
    id uuid NOT NULL,
    title character varying(255) NOT NULL,
    pendar_service_id uuid,
    metadata jsonb,
    id uuid NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone,
    service_status public.status DEFAULT 'new'::public.status
);

CREATE TABLE public.stat (
    id uuid NOT NULL,
    content_id uuid NOT NULL,
    profile_id uuid,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone,
    stat_log jsonb DEFAULT '{}'::jsonb NOT NULL,
    hit_time smallint DEFAULT 1 NOT NULL
);

CREATE TABLE public.tag (
    id uuid NOT NULL,
    title character varying(128) NOT NULL,
    category character varying(32) DEFAULT 'normal'::text NOT NULL,
    status public.status DEFAULT 'enable'::public.status NOT NULL,
    sum integer DEFAULT 0 NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone
);

CREATE TABLE public.tag_relation (
    tag_id uuid NOT NULL,
    content_id uuid NOT NULL,
    tag_type character varying(21) DEFAULT 'content'::text NOT NULL
);

CREATE TABLE public.token (
    id uuid NOT NULL,
    key character varying(64) NOT NULL,
    profile_id uuid NOT NULL,
    created_at timestamp with time zone DEFAULT now() NOT NULL,
    updated_at timestamp with time zone DEFAULT now(),
    deleted_at timestamp with time zone,
    status public.status DEFAULT 'new'::public.status NOT NULL,
    [password] character varying(16)
);

ALTER TABLE ONLY public.category
    ADD CONSTRAINT category_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.comment
    ADD CONSTRAINT comment_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.content
    ADD CONSTRAINT content_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.content_type
    ADD CONSTRAINT content_type_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.cp
    ADD CONSTRAINT cp_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public."like"
    ADD CONSTRAINT like_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.playlist
    ADD CONSTRAINT playlist_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.profile
    ADD CONSTRAINT profile_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.profile
    ADD CONSTRAINT profile_username_key UNIQUE (username);

ALTER TABLE ONLY public.service
    ADD CONSTRAINT service_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.stat
    ADD CONSTRAINT stat_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.tag
    ADD CONSTRAINT tag_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.tag_relation
    ADD CONSTRAINT tag_relation_pkey PRIMARY KEY (tag_id, content_id);

ALTER TABLE ONLY public.tag_relation
    ADD CONSTRAINT tag_relation_tag_id_content_id_key UNIQUE (tag_id, content_id);

ALTER TABLE ONLY public.token
    ADD CONSTRAINT token_pkey PRIMARY KEY (token_id, token_key);

ALTER TABLE ONLY public.token
    ADD CONSTRAINT token_token_key_key UNIQUE (token_key);


CREATE INDEX content_id ON public."like" USING btree (content_id);

CREATE UNIQUE INDEX cp_id ON public.cp USING btree (cp_id);

CREATE INDEX cp_phone ON public.cp USING btree (cp_phone);

CREATE UNIQUE INDEX like_profile_id_content_id ON public."like" USING btree (profile_id, content_id);

CREATE INDEX pendar_service_id ON public.service USING btree (pendar_service_id);

CREATE INDEX profile_id ON public."like" USING btree (profile_id);

CREATE INDEX service_title ON public.service USING btree (service_title);

CREATE UNIQUE INDEX token_token_key_idx ON public.token USING btree (token_key);

ALTER TABLE ONLY public.content
    ADD CONSTRAINT category_id FOREIGN KEY (category_id) REFERENCES public.category(category_id);

ALTER TABLE ONLY public.playlist
    ADD CONSTRAINT category_id FOREIGN KEY (category_id) REFERENCES public.category(category_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public."like"
    ADD CONSTRAINT content_id FOREIGN KEY (content_id) REFERENCES public.content(content_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.comment
    ADD CONSTRAINT content_id FOREIGN KEY (content_id) REFERENCES public.content(content_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.content
    ADD CONSTRAINT content_type_id FOREIGN KEY (content_type_id) REFERENCES public.content_type(content_type_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.service
    ADD CONSTRAINT cp_id FOREIGN KEY (cp_id) REFERENCES public.cp(cp_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.content
    ADD CONSTRAINT playlist_id FOREIGN KEY (playlist_id) REFERENCES public.playlist(playlist_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public."like"
    ADD CONSTRAINT profile_id FOREIGN KEY (profile_id) REFERENCES public.profile(profile_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.comment
    ADD CONSTRAINT profile_id FOREIGN KEY (profile_id) REFERENCES public.profile(profile_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.content
    ADD CONSTRAINT service_id FOREIGN KEY (service_id) REFERENCES public.service(service_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.category
    ADD CONSTRAINT service_id FOREIGN KEY (service_id) REFERENCES public.service(service_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.playlist
    ADD CONSTRAINT service_id FOREIGN KEY (service_id) REFERENCES public.service(service_id) ON UPDATE CASCADE ON DELETE CASCADE;

ALTER TABLE ONLY public.tag_relation
    ADD CONSTRAINT tag_relation_tag_id_fkey FOREIGN KEY (tag_id) REFERENCES public.tag(tag_id);

ALTER TABLE ONLY public.token
    ADD CONSTRAINT token_profile_id_fkey FOREIGN KEY (profile_id) REFERENCES public.profile(profile_id);

