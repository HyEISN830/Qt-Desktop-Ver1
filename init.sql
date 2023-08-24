-- Table machines start -------------------------------------------------------
drop table if exists machines;
CREATE TABLE public.machines (
	id bigserial PRIMARY KEY NOT NULL,
	"name" text NULL,
	ip text NULL,
	port text NULL,
	isdeleted bool NULL DEFAULT false
);
-- Table machines end -------------------------------------------------------

-- Table paras start -------------------------------------------------------
drop table if exists public.paras;
create table public.paras (
  id bigserial PRIMARY KEY NOT NULL  ,
  p0f1   text null,
  p0f2  text null,
  p0f3  text null,
  p0f4  text null,
  p0f5  text null,
  p0f6   text null,
  p0f7   text null,
  p1f1   text null,
  p1f2   text null,
  p1f3   text null,
  p1f4     text null,
  p1f5   text null,
  p1f6   text null,
  p1f7   text null,
  p1f8   text null,
  p1f9   text null,
  p1f10  text null,
  p2f1   text null,
  p2f2   text null,
  p2f3   text null,
  p2f4   text null,
  p2f5   text null,
  p2f6   text null,
  p2f7t  text null,
  p2f8t  text null,
  p2f9t  text null,
  p2f10t text null,
  p2f11t text null,
  p2f7b  text null,
  p2f8b  text null,
  p2f9b  text null,
  p2f10b text null,
  p2f11b text null,
  p2f12 text null,
  p3f1   text null,
  p3f2   text null,
  p3f3   text null,
  p3f4   text null,
  p3f5   text null,
  p3f6   text null,
  p3f7t   text null,
  p3f8t   text null,
  p3f9t   text null,
  p3f10t  text null,
  p3f11t  text null,
  p3f7b   text null,
  p3f8b   text null,
  p3f9b   text null,
  p3f10b text null,
  p3f11b text null,
  p3f12 text null,
  isdeleted bool NULL DEFAULT false
);

comment on column paras.p0f1 is '识别码开始位';
comment on column paras.p0f2 is '识别码';
comment on column paras.p0f3 is '机器类型';
comment on column paras.p0f4 is '标准机';
comment on column paras.p0f5 is '机型名称';
comment on column paras.p0f6 is '机型';
comment on column paras.p0f6 is '识别码结束位';
comment on column paras.p1f1 is '高压保护压力(Mpa)';
comment on column paras.p1f2 is '正压收氟报警压力(Mpa)';
comment on column paras.p1f3 is '高压保护延时(s)';
comment on column paras.p1f4 is '正压收氟报警延时(s)';
comment on column paras.p1f5 is '电流保护上限(A)';
comment on column paras.p1f6 is '正压收氟停机压力(Mpa)';
comment on column paras.p1f7 is '电流保护延时(s)';
comment on column paras.p1f8 is '正压收氟停机延时(s)';
comment on column paras.p1f9 is '低压保护压力(Mpa)';
comment on column paras.p1f10 is '低压保护延时(s)';
comment on column paras.p2f1 is '时间1(S)';
comment on column paras.p2f2 is '频率1(Hz)';
comment on column paras.p2f3 is '时间2(S)';
comment on column paras.p2f4 is '频率2(Hz)';
comment on column paras.p2f5 is '时间3(S)';
comment on column paras.p2f6 is '频率3(Hz)';
comment on column paras.p2f7t is '电流(A) 上限';
comment on column paras.p2f8t is '电流(A) 下限';
comment on column paras.p2f9t is '功率(W) 上限';
comment on column paras.p2f10t is '功率(W) 下限';
comment on column paras.p2f11t is '压力(Mpa) 上限';
comment on column paras.p2f7b is '压力(Mpa) 下限';
comment on column paras.p2f8b is '温差(°C) 上限';
comment on column paras.p2f9b is '温差(°C) 下限';
comment on column paras.p2f10b is '频率偏差(Hz) 上限';
comment on column paras.p2f11b is '频率偏差(Hz) 下限';
comment on column paras.p2f12 is '制热延时';
comment on column paras.p3f1 is '时间1(S)';
comment on column paras.p3f2 is '频率1(Hz)';
comment on column paras.p3f3 is '时间2(S)';
comment on column paras.p3f4 is '频率2(Hz)';
comment on column paras.p3f5 is '时间3(S)';
comment on column paras.p3f6 is '频率3(Hz)';
comment on column paras.p3f7t is '电流(A) 上限';
comment on column paras.p3f8t is '电流(A) 下限';
comment on column paras.p3f9t is '功率(W) 上限';
comment on column paras.p3f10t is '功率(W) 下限';
comment on column paras.p3f11t is '压力(Mpa) 上限';
comment on column paras.p3f7b is '压力(Mpa) 下限';
comment on column paras.p3f8b is '温差(°C) 上限';
comment on column paras.p3f9b is '温差(°C) 下限';
comment on column paras.p3f10b is '频率偏差(Hz) 上限';
comment on column paras.p3f11b is '频率偏差(Hz) 下限';
comment on column paras.p3f12 is '制冷延时';
-- Table paras end -------------------------------------------------------

-- Table tlogs start -------------------------------------------------------
CREATE TABLE public.tlogs (
	id bigserial primary key,
	testtime timestamp NULL,
	barcode text NULL,
	hotdiff real NULL,
	hoteleca real NULL,
	hotelecw real NULL,
	hotmpa real NULL,
	colddiff real NULL,
	coldeleca real NULL,
	coldelecw real NULL,
	coldmpa real NULL,
	workeleca real NULL,
	testresult varchar NULL,
	ip varchar
);

COMMENT ON COLUMN public.tlogs.testtime IS '测试时间';
COMMENT ON COLUMN public.tlogs.barcode IS '条码';
COMMENT ON COLUMN public.tlogs.hotdiff IS '制热温差';
COMMENT ON COLUMN public.tlogs.hoteleca IS '制热电流';
COMMENT ON COLUMN public.tlogs.hotelecw IS '制热功率';
COMMENT ON COLUMN public.tlogs.hotmpa IS '制热压力';
COMMENT ON COLUMN public.tlogs.colddiff IS '制冷温差';
COMMENT ON COLUMN public.tlogs.coldeleca IS '制冷电流';
COMMENT ON COLUMN public.tlogs.coldelecw IS '制冷功率';
COMMENT ON COLUMN public.tlogs.coldmpa IS '制冷压力';
COMMENT ON COLUMN public.tlogs.workeleca IS '工作电压';
COMMENT ON COLUMN public.tlogs.testresult IS '测试结果';
COMMENT ON COLUMN public.tlogs.ip IS 'IP';
-- Table tlogs end -------------------------------------------------------
