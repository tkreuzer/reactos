@ stdcall AuthzAccessCheck(long ptr ptr ptr ptr ptr long ptr ptr)
@ stdcall AuthzAddSidsToContext(ptr ptr long ptr long ptr)
@ stdcall AuthzCachedAccessCheck(long ptr ptr ptr ptr)
@ stdcall AuthzEnumerateSecurityEventSources(long ptr ptr ptr)
@ stub AuthzEvaluateSacl
@ stdcall AuthzFreeAuditEvent(ptr)
@ stdcall AuthzFreeContext(ptr)
@ stdcall AuthzFreeHandle(ptr)
@ stdcall AuthzFreeResourceManager(ptr)
@ stdcall AuthzGetInformationFromContext(ptr ptr long ptr ptr)
@ stdcall AuthzInitializeContextFromAuthzContext(long ptr ptr double ptr ptr)
@ stdcall AuthzInitializeContextFromSid(long ptr ptr ptr double ptr ptr)
@ stdcall AuthzInitializeContextFromToken(long ptr ptr ptr double ptr ptr)
@ stdcall AuthzInitializeObjectAccessAuditEvent(long ptr wstr wstr wstr wstr ptr long)
@ stdcall AuthzInitializeObjectAccessAuditEvent2(long ptr wstr wstr wstr wstr wstr ptr long)
@ stdcall AuthzInitializeResourceManager(long ptr ptr ptr wstr ptr)
@ stdcall AuthzInstallSecurityEventSource(long ptr)
@ stdcall AuthzOpenObjectAudit(long ptr ptr ptr ptr ptr long ptr)
@ stdcall AuthzRegisterSecurityEventSource(long ptr ptr)
@ varargs AuthzReportSecurityEvent(long ptr long ptr long)
@ stdcall AuthzReportSecurityEventFromParams(long ptr long ptr ptr)
@ stdcall AuthzUninstallSecurityEventSource(long wstr)
@ stdcall AuthzUnregisterSecurityEventSource(long ptr)
@ stub AuthziAllocateAuditParams
@ stub AuthziCheckContextMembership
@ stub AuthziFreeAuditEventType
@ stub AuthziFreeAuditParams
@ stub AuthziFreeAuditQueue
@ stub AuthziGenerateAdminAlertAuditW
@ stub AuthziInitializeAuditEvent
@ stub AuthziInitializeAuditEventType
@ stub AuthziInitializeAuditParams
@ stub AuthziInitializeAuditParamsFromArray
@ stub AuthziInitializeAuditParamsWithRM
@ stub AuthziInitializeAuditQueue
@ stub AuthziInitializeContextFromSid
@ stub AuthziLogAuditEvent
@ stub AuthziModifyAuditEvent2
@ stub AuthziModifyAuditEvent
@ stub AuthziModifyAuditEventType
@ stub AuthziModifyAuditQueue
@ stub AuthziQueryAuditPolicy
@ stub AuthziSetAuditPolicy
@ stub AuthziSourceAudit