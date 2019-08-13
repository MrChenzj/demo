--门诊候诊人数
 CREATE INDEX portal_his.idx_ms_ghmx_hzrs ON
    portal_his.ms_ghmx (
        YSDM,
        KSDM,
    nvl(
        JZJS, 0),
        THBZ,
        ZBLB,
    TO_CHAR(
        GHSJ, 'yyyy-mm-dd') );
---门诊检查
     create index PORTAL_HIS.IDX_MS_YJ01_TJFL on PORTAL_HIS.MS_YJ01(TJFL);
---
 create index PORTAL_HIS.IDX_YS_MZ_JBZD on
    PORTAL_HIS.YS_MZ_JBZD(JZXH,ZFPB);
---
create index PORTAL_HIS.IDX_MS_YJ01_JZXHFPHM on
    PORTAL_HIS.MS_YJ01(JZXH,FPHM);

---医生站
  create index PORTAL_HIS.IDX_YS_MZ_JZLS_BRBH on PORTAL_HIS.YS_MZ_JZLS(BRBH);